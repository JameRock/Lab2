#include <stdio.h>
#include <stdlib.h>

// Struc Node for linked list
typedef struct node {
    int data;
    struct node *next;
}
node;

void newList(struct node *list);

// Finding function
struct node * addList(struct node *jump, int data){
    struct node *newNode = NULL;
    if (jump == NULL)
    {
        jump = malloc( sizeof(struct node));
        // Malloc defend
        jump->data = data;
        jump->next = NULL;
        return jump;
    }
    //Find the bottom of the list starting from the base
    while (jump->next != NULL) //or while(p!= NULL)
    {
        jump = jump->next; //FJ was base NOT temp
    }
    //Now at the end of the list
    newNode = malloc( sizeof(struct node)); //get memory for new node
    //Defend against bad malloc
    jump->next = newNode; // add the new node to bottom of the list (FJ update)
    newNode->data = data; // slap the data into the list
    newNode->next = NULL; // terminate the list by setting next to NULL
    return jump; //return the new end of the list to the caller
    
    //Shouldnt we return newNode?
}

/*
 * Walk the list and print the data
 */

void printList(struct node** line)
{
    
    struct node* start;
    struct node* pause;
    if (*line == NULL) //If empty list
        
        return;
    
    
    start = *line;
    pause = start->next; //divide list in parts
    if (pause == NULL) //if single node
        return;
    newList(&pause);
    start->next->next = start; //reverse list around
    start->next = NULL;
    *line = pause;
}

void newList(struct node *list){
    while (list != NULL){
        fprintf(stdout, "data: %3d\n", list->data);
        list = list->next;
        
    }
    return;
}


struct node * insert(struct node * start, int dataNext, int newData)


{
    
    struct node * code = start;
    struct node * n;
    while(code != NULL && code->data != dataNext){
        
        code = code->next;
        
    }
    
    //return Null
    if(code == NULL)
        return NULL;
    
    n = (struct node*)malloc(sizeof(struct node));
    n->data = newData;
    n->next = code->next;
    code->next = n;
    return n;
}
struct node * find(struct node * start, int data)
{
    
    
    struct node * code = start;
    for(; code != NULL; code = code->next){
        
        if(code->data == data)
            return code;
    }
    
    return NULL; //Null not found
    
}
int delete(struct node * start, int data)
{
    struct node * code, * prev ;
    for(prev = NULL, code = start; code != NULL; code = code->next)
    {
        
        if(code->data == data)
            break;
        prev = code;
        
    }
    
    if(code == NULL)
        return 0;
    
    if(prev != NULL){
        
        //new link
        prev->next = code->next;
    }
    
    free(code);
    return 0;
    
}
/*
 * pass the input file to main, then add the data from the input file
 * to the list. NB The list starts as an empty list.
 */
int main(int argc, char **argv)
{
    struct node *root = NULL; // The root of the list
    struct node *temp = NULL;
    // struct node *base = NULL; // Placeholder for current end of the list
    char *inBuf = NULL; // input buffer
    int data = 0;
    int data1, tokencount; //tokencount delimit string
    char order;
    
    FILE * ifp;
    
    inBuf = malloc(100); //get a 100 character buffer for input data
    if (NULL == inBuf) // Check for success
    { //Let 'em know we failed to get a buffer
        fprintf(stderr, "No memory - good bye!\n");
        return -1;
    }
    ifp = fopen(argv[1], "rwb"); //Get the filename from the command line
    if (NULL == ifp) // Check for success
    { //Let 'em know the filename wasn't found
        fprintf(stderr, "%s file not found.\n", argv[1]);
        return -1;
    }
    /*
     * Read the file, then add the data to the list
     * All the while keep track of the last added node in temp
     */
    while (fscanf(ifp, "%[^\n]\n", inBuf) != EOF)
    {
        
        
        fprintf(stdout, "%s\n", inBuf);
        //data = atoi(inBuf);
        
        
        //parse
        tokencount = sscanf(inBuf, "%c%d%d", &order, &data, &data1);
        switch(order){
            case 'i':
            {
                if(tokencount == 2){
                    
                    
        //So add a new node & fill it with data
        if (NULL == root) // First node add to the list
        {
        temp = root = addList(root, data);
        }
        else{
        // add to the bottom of the list
        temp = addList(root, data);
        }
        if (NULL == temp){
        printf("Failed to add -- Good bye\n");
        return -1;
        }
        else{
    printf("Successfully add\n");
    }
    }
    else if(tokencount == 3) {
        temp = insert(root, data, data1);
        if(temp == NULL){
    printf("Failed to add after\n");
    }
    else {
    printf("Successfully add\n");
    }
    }
    }
        break;
        case 'f': {
        if(find(root, data) == NULL) {
        printf("Not found\n");
    }
        else {
        printf("Found\n");
    }
    }
    break;
    case 'd': {
                
    if(delete(root,data)) {
    printf("Failed to delete\n");
}
    else
    printf("Successfully deleted\n");
}
    case 'p': {
    printList(root);
}
                
    break;
    case 'r': newList(&root); //reverse r option
    break;
    }
    break;
        
    }
    fclose(ifp);
    return 0;
}
