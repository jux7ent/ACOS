/*
 * Обработать строки a.a.a.a..a.a.a.a и т.д.
 * */

#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ftw.h>
#include <pwd.h>
#include <grp.h>
#include <memory.h>
#include <stdlib.h>

typedef struct dir_info_arr dir_info_arr;
typedef struct dirent dirent;

int cmpfunc(const void *a, const void *b) {
    const dirent **ia = (const dirent **)a;
    const dirent **ib = (const dirent **)b;

    return strcmp((*ia)->d_name, (*ib)->d_name);
}

struct dir_info_arr {
    dirent **arr_;
    size_t size_;
    size_t capacity_;
};

dir_info_arr *new_dir_info_arr() {
    dir_info_arr *result = (dir_info_arr *)malloc(sizeof(dir_info_arr));
    result->size_ = 0;
    result->capacity_ = 256;
    result->arr_ = (dirent **)malloc(sizeof(dirent *) * result->capacity_);

    return result;
}

void push_to_dir_info(dir_info_arr *dia, dirent *d) {
    dia->arr_[dia->size_] = d;
    ++dia->size_;

    if (dia->size_ >= dia->capacity_) {
        dia->capacity_ *= 2;
        dia->arr_ = (dirent **)realloc(dia->arr_, sizeof(dirent *) * dia->capacity_);
    }
}



void print_filetype(mode_t mode) {
    /*switch (mode & S_IFMT) {
        case S_IFREG: putchar('-'); break;
        case S_IFDIR: putchar('d'); break;
        case S_IFLNK: putchar('l'); break;
        case S_IFCHR: putchar('c'); break;
        case S_IFBLK: putchar('b'); break;
        case S_IFSOCK: putchar('s'); break;
        case S_IFIFO: putchar('f'); break;
        default: putchar('-'); break;
    }*/
    if (S_ISREG(mode))
        putchar('-');
    else if (S_ISDIR(mode))
        putchar('d');
    else if (S_ISLNK(mode))
        putchar('l');
    else if (S_ISCHR(mode))
        putchar('c');
    else if (S_ISBLK(mode))
        putchar('b');
    else if (__S_ISTYPE((mode), __S_IFSOCK))
        putchar('s');
    else if (S_ISFIFO(mode))
        putchar('p');
    else
        putchar('-');
}

void print_permissions(mode_t mode) {
    putchar((mode & S_IRUSR) ? 'r' : '-');
    putchar((mode & S_IWUSR) ? 'w' : '-');
    putchar((mode & S_IXUSR) ? 'x' : '-');
    putchar((mode & S_IRGRP) ? 'r' : '-');
    putchar((mode & S_IWGRP) ? 'w' : '-');
    putchar((mode & S_IXGRP) ? 'x' : '-');
    putchar((mode & S_IROTH) ? 'r' : '-');
    putchar((mode & S_IWOTH) ? 'w' : '-');
    putchar((mode & S_IXOTH) ? 'x' : '-');
}

void print_ug_name(__uid_t st_uid, __gid_t st_gid) {
    struct passwd *pw = getpwuid(st_uid); //for username
    struct group  *gr = getgrgid(st_gid); //for groupname

    if (pw == NULL) {
        printf("%d ", st_uid);
    } else {
        printf("%s ", pw->pw_name);
    }

    if (gr == NULL) {
        printf("%d ", st_gid);
    } else {
        printf("%s ", gr->gr_name);
    }
}

dir_info_arr  *pr(dir_info_arr *arr, char *prefix) {
    struct stat sb;
    struct passwd *pw;
    struct group *gr;

    char path[2048];
    char link_buff[1024];
    path[0] = 0;
    strcat(path, prefix);
    size_t len = strlen(path);
    if (path[len - 1] != '/') {
        path[len] = '/';
        ++len;
    }

    size_t size_dirs = 0;

    for (size_t i = 0; i < arr->size_; ++i) {
        if (arr->arr_[i]->d_name[0] == '.') {
            continue;
        }
        path[len] = 0;
        strcat(path, arr->arr_[i]->d_name);
        if (lstat(path, &sb) == -1) {
            perror("lstat");
        }

        print_filetype(sb.st_mode);
        print_permissions(sb.st_mode);
        printf(" %lu ", sb.st_nlink);
        print_ug_name(sb.st_uid, sb.st_gid);
        printf("%lu %s", sb.st_size, arr->arr_[i]->d_name);
        if (S_ISLNK(sb.st_mode)) { //print symbolic link
            ssize_t l = readlink(path, link_buff, sizeof(link_buff));
            if (l >= 0) {
                link_buff[l] = 0;
                printf(" -> %s", link_buff);
            }
        }
        printf("\n");

        if (S_ISDIR(sb.st_mode)) {
            arr->arr_[size_dirs] = arr->arr_[i];
            ++size_dirs;
        }
        /*if (arr->arr_[i]->d_type == FTW_D) {
            arr->arr_[size_dirs] = arr->arr_[i];
            ++size_dirs;
        }*/
    }

    arr->size_ = size_dirs;
    return arr;
}

void file_tree_walk(char *pathname, dir_info_arr  *(*pr)(dir_info_arr *arr, char *prefix)) {
    DIR *dir = opendir(pathname);
    dir_info_arr *dia = new_dir_info_arr();
    struct dirent *dir_info;

    if (dir) {
        printf("%s:\n", pathname);
        while ((dir_info = readdir(dir)) != NULL) {
            push_to_dir_info(dia, dir_info);
        }
        qsort(dia->arr_, dia->size_, sizeof(dia->arr_), cmpfunc);
        dia = pr(dia, pathname);
        char path[2048];
        path[0] = 0;

        strcat(path, pathname);
        size_t len = strlen(path);

        if (path[len - 1] != '/') {
            path[len] = '/';
            path[len + 1] = '\0';
            ++len;
        }

        for (size_t i = 0; i < dia->size_; ++i) {
            path[len] = 0;
            strcat(path, dia->arr_[i]->d_name);

            file_tree_walk(path, pr);
        }
        closedir(dir);
    } else {
        perror(pathname);
        return;
    }
}

int main(int argc, char **argv) {
    if (argc == 1) {
        file_tree_walk(".", &pr);
        return 0;
    }

    file_tree_walk(argv[1], &pr);

    return 0;
}