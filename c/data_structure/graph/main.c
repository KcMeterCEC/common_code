#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "bfs.h"

vertex_t vertexes[] = 
{
    {
        .name = "you",//0
    },
    {
        .name = "Abish",//1
    },
    {
        .name = "Robi",//2
    }, 
    {
        .name = "Roze",//3
    },
    {
        .name = "Bob",//4
    },           
    {
        .name = "Tevin",//5
    },
    {
        .name = "Octavio",//6
    },   
    {
        .name = "Antwan",//7
    },
    {
        .name = "Estevan",//8
    },     
    {
        .name = "Antoine",//9
    },
    {
        .name = "Gustavo",//10
        .has_key = true,
    },    
};

int main(int argc, char *argv[])
{
    bfs_str_init();

    map_t *map = bfs.create_map(vertexes, sizeof(vertexes) / sizeof(vertex_t));

    //you
    bfs.add_edge(map, &vertexes[0], &vertexes[1]);
    bfs.add_edge(map, &vertexes[0], &vertexes[2]);
    bfs.add_edge(map, &vertexes[0], &vertexes[3]);

    //Abish
    bfs.add_edge(map, &vertexes[1], &vertexes[4]);
   
    //Robi
    bfs.add_edge(map, &vertexes[2], &vertexes[7]);
    bfs.add_edge(map, &vertexes[2], &vertexes[3]);
   
    //Roze
    bfs.add_edge(map, &vertexes[3], &vertexes[8]);

    //Bob
    bfs.add_edge(map, &vertexes[4], &vertexes[5]);    
    bfs.add_edge(map, &vertexes[4], &vertexes[2]);    

    //Tevin
    bfs.add_edge(map, &vertexes[5], &vertexes[6]);    
    bfs.add_edge(map, &vertexes[5], &vertexes[2]); 

    //Octavio
    bfs.add_edge(map, &vertexes[6], &vertexes[10]);    
    bfs.add_edge(map, &vertexes[6], &vertexes[7]);    

    //Antwan
    bfs.add_edge(map, &vertexes[7], &vertexes[10]);  

    //Estevan
    bfs.add_edge(map, &vertexes[8], &vertexes[7]);      
    bfs.add_edge(map, &vertexes[8], &vertexes[9]);   

    //Antoine
    bfs.add_edge(map, &vertexes[9], &vertexes[10]);       

    bfs.print_map(map);

    bfs.find_key(map, &vertexes[0]);
    return 0;
}