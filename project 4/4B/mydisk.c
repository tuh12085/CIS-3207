#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include "struct.h"
// --------------------------------------------- Global Var ---------------------------------------------//
int number_of_block = 60;
int each_block_size = 16; 
int fd;

int file_information_index; // for disk_split() function;
int fat_table_storage_index; // for disk_split() function;
int data_entry_index; // for disk_split() function;

int root_index = 0; //the root;

int data_block_checking_list[100];//{1,0,1,0,0,0,1} tracking of the block whether it used; 
//the int inside of the list can be motify;

struct Direction* current_direction; // root;

// --------------------------------------------- Global Var ---------------------------------------------//

// --------------------------------------------- Partition a disk ---------------------------------------------//
int disk_split(){
    file_information_index = 0;
    fat_table_storage_index = number_of_block / 3;
    data_entry_index = fat_table_storage_index * 2;
    return 0;
}

// --------------------------------------------- Create a disk ---------------------------------------------//
int create_disk(char *name ){
    int file_size_counter;
    fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);  


    disk_split();

    char buf[each_block_size];
    memset(buf, 0, each_block_size);

    for (file_size_counter = 0;  file_size_counter < number_of_block; file_size_counter++){
                write(fd, buf, each_block_size);
        }

    close(fd);
    return 0;
  
}

// --------------------------------------------- Open a disk ---------------------------------------------//
int open_disk(char *name){
    fd = open(name,O_RDWR,0644);
    return 0;
}

// --------------------------------------------- Write a disk/block ---------------------------------------------//
int write_disk(int block_index, char* words){
      
    lseek(fd, block_index * each_block_size, SEEK_SET);
    write(fd,words,strlen(words));    

    return 0;
}
// --------------------------------------------- Read a disk/block ---------------------------------------------//
// 0 - > NULL, 1 - > HAS SOMETHING
int read_disk(int block_index){


    lseek(fd, block_index * each_block_size, SEEK_SET);    
    char read_buffer[each_block_size];
    read(fd,read_buffer,each_block_size);
    

    if(strcmp(read_buffer, "\0") == 0){
        printf("It is empty\n");
        return 0;
    }else{
        printf("%s\n",read_buffer);
        return 1;
    }
    
}
// --------------------------------------------- Delete a disk/block ---------------------------------------------//

int detele_block(int block_index){
    lseek(fd, block_index * each_block_size, SEEK_SET);  
    // slight change here
    char buf[each_block_size];
    memset(buf, 0, strlen(buf));
    write(fd, buf, strlen(buf));    
    return 0;
}
// --------------------------------------------- Close a disk ---------------------------------------------//
int close_disk(int fd){
    close(fd);
    return 0;
}



// Note: Above is the creation of a disk; working on nov 17,2019; 







// --------------------------------------------- File function---------------------------------------------//


// --------------------------------------------- Create a File---------------------------------------------//
int Create_file(char *filename){
    

    return 0;
}

int Write_file(char* filename, char* words){

    return 0;
}
// --------------------------------------------- Read a File---------------------------------------------//
int Read_file(char *filename){
    return 0;
}

// --------------------------------------------- Delete a File---------------------------------------------//
int Delete_file(char *filename){
    return 0;
}
// --------------------------------------------- Create a Direction---------------------------------------------//
// working .............
int Create_directory(char *dirname, int current_d_index, int previous_d_index){

    // check if the dirname exit;


    struct Direction* new_direction = (struct Direction*) malloc(sizeof(struct Direction));        
    new_direction->current_index = current_d_index;
    new_direction->previous_index = previous_d_index;


    return 1;
}
// --------------------------------------------- Find a Direction---------------------------------------------//

int Fine_directory(char *dirname){
    return 0;
}
// --------------------------------------------- Delete a Direction ---------------------------------------------//

int Delete_directory(char *dirname){
    return 0;
}




// --------------------------------------------- Main ---------------------------------------------//
int main(){ 
    printf("\n\n\n");
    
    char name[] = "disk";
    
    create_disk(name);
    open_disk(name);
    write_disk(file_information_index,"first part");
    write_disk(fat_table_storage_index,"second part");
    write_disk(data_entry_index,"third part");
    read_disk(file_information_index);
    current_direction =(struct Direction*) malloc(sizeof(struct Direction));            


    //testing
    current_direction->current_index = 2;
    printf("%d\n",current_direction->current_index);

    close_disk(fd);    
    printf("\n\n\n");
    return 0;
}