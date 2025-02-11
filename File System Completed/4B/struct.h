#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>



#define name_size  10   //define
#define bloc_entry_number  10   // for calculation
// DIY the var here:
// These three has to be the same here;
#define direction_list 10  // [#] plugin number
#define file_list 10     // [#] plugin number
#define block_list 10   // [#] plugin number



// Note from myself: Assignment requirement;
// 16,384 blocks total     ---- 2^14
// 8,192 for data blocks   ----- 2^13
// 8191 for meda -- 2^13 - 1
// 1 for super   --- 2^0
/*
just for testing easy to read;
super - > 1;
meta -  > 32 --- 2^5;
data - > 32 ---> 2^5;
*/
//-------------------------------------------------------------------------------------------------------->
struct File;
struct Direction;
struct Block;

struct File {
    char name[name_size]; //index of the block which contains the imformation of the file;
    int below_direction;
    int used;
    int first_block_entry;
    char time_of_creation[30];
};

struct Direction{
    char name[name_size];// name of the direction
    int current_index;
    int previous_index;
    int used;
    int n_things_inside;
    char time_of_creation[30];
    // add additional imformation here
};

struct Block{
    int next_block; // the id / the index of the block
    int size_remain; // the size of a single block remain
    int is_full;
    int used;
};
// ---------------- Function declares ---------------------------
int char_reset(void);
int parsing(void);



// ----- NEW ELEMENT FOR META BLOCK FEATURE-----
int updating_metablock(struct Direction *dirlist[], struct File *filelist[]);
int write_metablock_special(int block_index,int special, char item[]);
int loading(struct Direction *dirtable[], struct File *filetable[]);
// ----- NEW ELEMENT FOR META BLOCK-----


int Mount(char *name);
int Unmount(int fd);

int get_free_space_dirtable(struct Direction *list[]);
int get_free_space_filetable(struct File *list[]);
int init_dir(struct Direction *list[]);
int init_root(struct Direction *list[]);

int create_disk(char *name);
int open_disk(char *name);
int write_disk(int block_index, char* words);
int read_disk(int block_index);
int delete_block(int block_index);
int close_disk(int fd);

int init_block_allocation(void);
int init_block(struct Block *lisk[]);

int init_file(struct File *list[]);
int Create_file(char *filename, struct Direction *current_dir,struct Direction *dir_table[],struct File *file_table[]);
int Write_file(char *filename, struct Direction *current_dir,struct Direction *dir_table[],struct File *file_table[],struct Block *block_table[]);
int Read_file(char *filename, struct Direction *dir_table[], struct Direction *current_dir,struct File *file_table[]);
int Delete_file(char *filename, struct Direction *dir_table[], struct Direction *current_dir,struct File *file_table[]);


int Create_directory(char *dirname, struct Direction *dir_table[], struct Direction *current_dir);
int Change_directory(char *dirname,struct Direction *current_dir, struct Direction *dir_table[]);
int Delete_directory(char *dirname, struct Direction *dir_table[], struct Direction *current_dir,struct File *file_table[]);
void print_direction( struct Direction *dir,struct Direction *list[],struct File *file_table[]);

int help(void);
int print_livoidst(void);
int begin(void);

// ---------------- Function declares ---------------------------
