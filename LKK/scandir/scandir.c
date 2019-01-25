#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#define DIR_PATH "./sdcard/"

/* support music format */
const char *support_type[10]= {
	[0] = ".mp3",
	[1] = ".MP3",
	[2] = ".flac",
	[3] = ".ape",
	[4] = ".ogg",
	[5] = ".m4a",
	[6] = ".aac",
	[7] = ".wav",
	[8] = ".WAV",
	[9] = ".amr"
};

int filter(const struct dirent *dir)
{
	int index = 0;

	for (index = 0; index < sizeof(support_type)/sizeof(char *); index++)
		if(strstr(dir->d_name, support_type[index]) != NULL) {
			return 1;
		}

	return 0;
}

int main()
{
	DIR *dirp = NULL;
	struct dirent **namelist;
	struct dirent *entp;
	int dir_entry, i;
	char buff[512];

	if ((dirp = opendir(DIR_PATH)) == NULL) {
		printf("opendir fail\n");
		return -1;
	}

	while ((entp = readdir(dirp)) != NULL) {
		if (strcmp(".", entp->d_name) == 0 || strcmp("..", entp->d_name) == 0)
			continue;

		if (entp->d_type & DT_DIR) {
			sprintf(buff, "%s%s", DIR_PATH, entp->d_name);
			puts(" ");
			printf("dirent path: %s\n", buff);

			dir_entry = scandir(buff, &namelist, filter, alphasort);
			printf("file entry: %d\n", dir_entry);
			for (i = 0; i < dir_entry ; i++) {
				sprintf(buff, "%s", namelist[i]->d_name);
				puts(buff);
				free(namelist[i]);
			}
		}
	}
	free (namelist);

	return 0;

}
