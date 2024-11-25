#include <dirent.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

void search_and_remove(const char *directory_path, const char *destName)
{
    struct dirent *entry;
    DIR *dir = opendir(directory_path);

    if (dir == NULL)
    {
        perror("Failed to open directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        // readdir includes "." and ".." "files" so i exclude them
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", directory_path, entry->d_name);

        struct stat path_stat;
        if (stat(full_path, &path_stat) < 0)
        {
            perror("Error getting file information");
            continue;
        }

        if (S_ISDIR(path_stat.st_mode))
        {
            search_and_remove(full_path, destName);
        }
        else if (S_ISREG(path_stat.st_mode))
        {
            if (strcmp(entry->d_name, destName) == 0)
            {
                if (remove(full_path) == 0)
                {
                    printf("Removed file: \"%s\"\n", full_path);
                }
                else
                {
                    perror("Error deleting file");
                }
            }
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s <directory> <file_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *sourceFolder = argv[1];
    const char *destName = argv[2];

    search_and_remove(sourceFolder, destName);

    return EXIT_SUCCESS;
}
