#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define src 0

void generateEdgesWorking(int, int, int);
void generateEdgesNotWorking(int, int, int);
void generateNodes();
void dijkstra();
void display();

int rows, i, j;
float edgeStartX, edgeStartY;
bool working = false;

vector<vector<int>> graph;

vector<int> temp;

void mainHeading()
{
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0, 1.0, 1.0);

        glRasterPos2f(-0.4f, 0.9f);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>("DIJKSTRA ALGORITHM"));
}

void generateNodes()
{
        int iteratorNodeValues = 1;

        float startX = -0.2f, startY = 0.5f;
        edgeStartX = startX;
        edgeStartY = startY;

        int prevCounter = 0, counter = 1;

        for (i = 0; i < rows; i++)
        {
                for (j = 0; j < rows; j++)
                {

                        // red color primitive
                        glColor3f(1.0f, 0.0f, 0.0f);

                        if (graph[i][j] != 0)
                        {
                                if (startX < 0)
                                {
                                        glBegin(GL_POLYGON);
                                        glVertex2f(startX, startY);
                                        glVertex2f(startX - 0.2, startY);
                                        glVertex2f(startX - 0.2, startY + 0.2);
                                        glVertex2f(startX, startY + 0.2);
                                        glEnd();
                                }
                                else
                                {
                                        glBegin(GL_POLYGON);
                                        glVertex2f(startX, startY);
                                        glVertex2f(startX + 0.2, startY);
                                        glVertex2f(startX + 0.2, startY + 0.2);
                                        glVertex2f(startX, startY + 0.2);
                                        glEnd();
                                }

                                // white color primitive
                                glColor3f(1.0f, 1.0f, 1.0f);
                                if (startX < 0)
                                {
                                        float numX = startX - 0.1f, numY = startY + 0.1f;
                                        glRasterPos2f(numX, numY);
                                }
                                else
                                {
                                        float numX = startX + 0.1f, numY = startY + 0.1f;
                                        glRasterPos2f(numX, numY);
                                }
                                string str = to_string(iteratorNodeValues++);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }
                                prevCounter++;
                                break;
                        }
                }
                if (prevCounter == counter)
                {

                        counter++;
                        if (counter == 3 || counter == 4)
                        {
                                if (startX != -0.4f && startY != 0.1f)
                                {
                                        startX = -0.4f;
                                        startY = 0.1f;
                                }
                                else
                                {
                                        startX += 0.8f;
                                }
                        }
                        else if (counter == 5 || counter == 6)
                        {
                                if (startX != -0.2f && startY != -0.3f)
                                {
                                        startX = -0.2f;
                                        startY = -0.3f;
                                }
                                else
                                {
                                        startX += 0.4f;
                                }
                        }
                        else
                        {
                                startX += 0.4f;
                        }
                }
        }

        if(working==false){
                for (i = 0; i < rows; i++)
                {
                        for (j = i; j < rows; j++)
                        {
                                if (graph[i][j] != 0)
                                {
                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                }
                        }
                }
                dijkstra();
        }
        
}

void dijkstra()
{
        working = true;

        int dis[rows], i, j, final[rows], final_indexes = 1;

        for (i = 0; i < rows; i++)
        {
                dis[i] = 999;
                final[i] = 0;
        }

        dis[src] = 0;
        final[src] = 1;

        // algorithm starts

        int mini;
        i = src;

        while (final_indexes <= rows)
        {
                mini = 999;
                for (j = 0; j < rows; j++)
                {

                        if (graph[i][j] != 0 && final[j] != 1)
                        {
                                generateEdgesWorking(i, j, graph[i][j]);

                                if (dis[i] + graph[i][j] < dis[j])
                                {
                                        dis[j] = dis[i] + graph[i][j];
                                }
                        }
                }

                for (j = 0; j < rows; j++)
                {
                        if (dis[j] < mini && final[j] != 1)
                        {
                                mini = dis[j];
                                i = j;
                        }
                }
                final[i] = 1;
                final_indexes++;
        }

        cout<<endl<<"Shortest distances from source node 1 are : "<<endl;
        for(i=0; i<rows; i++) cout<<dis[i]<<" ";
}

void generateEdgesWorking(int row, int col, int cost)
{
        glLineWidth(2.0f);

                if (row == 0) // node 1
                {
                        if (col == 1) // node 2
                        {
                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                //clear the screen
                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);
                                glutSwapBuffers();
                                
                                //generating rest componenets 
                                mainHeading();
                                generateNodes();
                                glutSwapBuffers();

                                glColor3f(1.0, 0.0f, 0.0f); // red color
                                glBegin(GL_LINES);
                                glVertex2f(-0.2f, 0.6f);
                                glVertex2f(0.2f, 0.6f);
                                glEnd();

                                glRasterPos2f(0.0f, 0.7f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }

                                 glutSwapBuffers();

                                //generating working edges
                                for(i=0; i<rows; i++){
                                        for(j=i; j<rows; j++){
                                                if(i==row && j==col) continue;
                                                else if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                //generating white edges
                                for(i=0; i<rows; i++){
                                        for(j=0; j<rows; j++){
                                                if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(1000);
                                glutSwapBuffers();

                        }
                        else if (col + 1 == 3) // node 3
                        {
                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                glColor3f(1.0f, 0.0f, 0.0f);
                                glBegin(GL_LINES);
                                glVertex2f(-0.3f, 0.5f);
                                glVertex2f(-0.5f, 0.3f);
                                glEnd();
                                glRasterPos2f(-0.5f, 0.4f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }

                                glutSwapBuffers();

                                //generating working edges
                                for(i=0; i<rows; i++){
                                        for(j=i; j<rows; j++){
                                                if(i==row && j==col) continue;
                                                else if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                //generating white edges
                                for(i=0; i<rows; i++){
                                        for(j=0; j<rows; j++){
                                                if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(1000);
                                glutSwapBuffers();
                        }
                        else if (col + 1 == 4) // node 4
                        {
                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                glColor3f(1.0, 0.0f, 0.0f); // red color
                                glBegin(GL_LINES);
                                glVertex2f(-0.3f, 0.5f);
                                glVertex2f(0.4f, 0.3f);
                                glEnd();

                                glRasterPos2f(0.15f, 0.46f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }

                                 glutSwapBuffers();

                                //generating working edges
                                for(i=0; i<rows; i++){
                                        for(j=i; j<rows; j++){
                                                if(i==row && j==col) continue;
                                                else if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                //generating white edges
                                for(i=0; i<rows; i++){
                                        for(j=0; j<rows; j++){
                                                if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(1000);
                                glutSwapBuffers();
                        }
                        else if (col + 1 == 5) // node 5
                        {
                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                glColor3f(1.0, 0.0f, 0.0f); // red color
                                glBegin(GL_LINES);
                                glVertex2f(-0.3f, 0.5f);
                                glVertex2f(-0.3f, -0.1f);
                                glEnd();

                                glRasterPos2f(-0.3f, 0.3f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }

                                 glutSwapBuffers();

                                //generating working edges
                                for(i=0; i<rows; i++){
                                        for(j=i; j<rows; j++){
                                                if(i==row && j==col) continue;
                                                else if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                //generating white edges
                                for(i=0; i<rows; i++){
                                        for(j=0; j<rows; j++){
                                                if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(1000);
                                glutSwapBuffers();
                        }
                        else if (col + 1 == 6) // node 6
                        {
                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                glColor3f(1.0, 0.0f, 0.0f); // red color
                                glBegin(GL_LINES);
                                glVertex2f(-0.3f, 0.5f);
                                glVertex2f(0.2f, -0.1f);
                                glEnd();

                                glRasterPos2f(-0.1f, 0.3f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }

                                 glutSwapBuffers();

                                //generating working edges
                                for(i=0; i<rows; i++){
                                        for(j=i; j<rows; j++){
                                                if(i==row && j==col) continue;
                                                else if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                //generating white edges
                                for(i=0; i<rows; i++){
                                        for(j=0; j<rows; j++){
                                                if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(1000);
                                glutSwapBuffers();
                        }
                }
                else if (row + 1 == 2) // node 2
                {
                        if (col + 1 == 3) // node 3
                        {
                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                glColor3f(1.0, 0.0f, 0.0f); // red color
                                glBegin(GL_LINES);
                                glVertex2f(0.3f, 0.5f);
                                glVertex2f(-0.5f, 0.3f);
                                glEnd();

                                glRasterPos2f(0.1f, 0.5f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }

                                 glutSwapBuffers();
                        }
                        else if (col + 1 == 4) // node 4
                        {
                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                glColor3f(1.0, 0.0f, 0.0f); // red color
                                glBegin(GL_LINES);
                                glVertex2f(0.3f, 0.5f);
                                glVertex2f(0.5f, 0.3f);
                                glEnd();

                                glRasterPos2f(0.5f, 0.4f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }

                                 glutSwapBuffers();

                               //generating working edges
                                for(i=0; i<rows; i++){
                                        for(j=i; j<rows; j++){
                                                if(i==row && j==col) continue;
                                                else if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                //generating white edges
                                for(i=0; i<rows; i++){
                                        for(j=0; j<rows; j++){
                                                if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(1000);
                                glutSwapBuffers();
                        }
                        else if (col + 1 == 5) // node 5
                        {
                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                glColor3f(1.0, 0.0f, 0.0f); // red color
                                glBegin(GL_LINES);
                                glVertex2f(0.3f, 0.5f);
                                glVertex2f(-0.3f, -0.1f);
                                glEnd();

                                glRasterPos2f(0.05f, 0.3f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }

                                 glutSwapBuffers();

                                //generating working edges
                                for(i=0; i<rows; i++){
                                        for(j=i; j<rows; j++){
                                                if(i==row && j==col) continue;
                                                else if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                //generating white edges
                                for(i=0; i<rows; i++){
                                        for(j=0; j<rows; j++){
                                                if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(1000);
                                glutSwapBuffers();
                        }
                        else if (col + 1 == 6) // node 6
                        {
                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                glColor3f(1.0, 0.0f, 0.0f); // red color
                                glBegin(GL_LINES);
                                glVertex2f(0.3f, 0.5f);
                                glVertex2f(0.3f, -0.1f);
                                glEnd();

                                glRasterPos2f(0.25f, 0.25f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }

                                 glutSwapBuffers();

                                //generating working edges
                                for(i=0; i<rows; i++){
                                        for(j=i; j<rows; j++){
                                                if(i==row && j==col) continue;
                                                else if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                //generating white edges
                                for(i=0; i<rows; i++){
                                        for(j=0; j<rows; j++){
                                                if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(1000);
                                glutSwapBuffers();
                        }
                }
                else if (row + 1 == 3) // node 3
                {
                        if (col + 1 == 4) // node 4
                        {
                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                glColor3f(1.0, 0.0f, 0.0f); // red color
                                glBegin(GL_LINES);
                                glVertex2f(-0.4f, 0.2f);
                                glVertex2f(0.4f, 0.2f);
                                glEnd();

                                glRasterPos2f(-0.2f, 0.15f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }

                                 glutSwapBuffers();

                                //generating working edges
                                for(i=0; i<rows; i++){
                                        for(j=i; j<rows; j++){
                                                if(i==row && j==col) continue;
                                                else if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                //generating white edges
                                for(i=0; i<rows; i++){
                                        for(j=0; j<rows; j++){
                                                if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(1000);
                                glutSwapBuffers();
                        }
                        else if (col + 1 == 5) // node 5
                        {
                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                glColor3f(1.0, 0.0f, 0.0f); // red color
                                glBegin(GL_LINES);
                                glVertex2f(-0.5f, 0.1f);
                                glVertex2f(-0.3f, -0.1f);
                                glEnd();

                                glRasterPos2f(-0.5f, -0.1f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }

                                 glutSwapBuffers();

                                //generating working edges
                                for(i=0; i<rows; i++){
                                        for(j=i; j<rows; j++){
                                                if(i==row && j==col) continue;
                                                else if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                //generating white edges
                                for(i=0; i<rows; i++){
                                        for(j=0; j<rows; j++){
                                                if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(1000);
                                glutSwapBuffers();
                        }
                        else if (col + 1 == 6) // node 6
                        {
                               glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                glColor3f(1.0, 0.0f, 0.0f); // red color
                                glBegin(GL_LINES);
                                glVertex2f(-0.5f, 0.1f);
                                glVertex2f(0.3f, -0.1f);
                                glEnd();

                                glRasterPos2f(-0.05f, 0.0f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }

                                 glutSwapBuffers();

                               //generating working edges
                                for(i=0; i<rows; i++){
                                        for(j=i; j<rows; j++){
                                                if(i==row && j==col) continue;
                                                else if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                //generating white edges
                                for(i=0; i<rows; i++){
                                        for(j=0; j<rows; j++){
                                                if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(1000);
                                glutSwapBuffers();
                        }
                }
                else if (row + 1 == 4) // node 4
                {
                        if (col + 1 == 5) // node 5
                        {
                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                glColor3f(1.0, 0.0f, 0.0f); // red color
                                glBegin(GL_LINES);
                                glVertex2f(0.5f, 0.1f);
                                glVertex2f(-0.3f, -0.1f);
                                glEnd();

                                glRasterPos2f(0.2f, 0.05f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }

                                 glutSwapBuffers();

                                //generating working edges
                                for(i=0; i<rows; i++){
                                        for(j=i; j<rows; j++){
                                                if(i==row && j==col) continue;
                                                else if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                //generating white edges
                                for(i=0; i<rows; i++){
                                        for(j=0; j<rows; j++){
                                                if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(1000);
                                glutSwapBuffers();
                        }
                        else if (col + 1 == 6) // node 6
                        {
                               glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                glColor3f(1.0, 0.0f, 0.0f); // red color
                                glBegin(GL_LINES);
                                glVertex2f(0.5f, 0.1f);
                                glVertex2f(0.3f, -0.1f);
                                glEnd();

                                glRasterPos2f(0.5f, -0.1f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }

                                 glutSwapBuffers();

                                //generating working edges
                                for(i=0; i<rows; i++){
                                        for(j=i; j<rows; j++){
                                                if(i==row && j==col) continue;
                                                else if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                //generating white edges
                                for(i=0; i<rows; i++){
                                        for(j=0; j<rows; j++){
                                                if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(1000);
                                glutSwapBuffers();
                        }
                }
                else if (row + 1 == 5) // node 5
                {
                        if (col + 1 == 6) // node 6
                        {
                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                glColor3f(1.0, 0.0f, 0.0f); // red color
                                glBegin(GL_LINES);
                                glVertex2f(-0.2f, 0.2f);
                                glVertex2f(0.2f, -0.2f);
                                glEnd();

                                glRasterPos2f(0.0f, -0.3f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }

                                 glutSwapBuffers();

                                //generating working edges
                                for(i=0; i<rows; i++){
                                        for(j=i; j<rows; j++){
                                                if(i==row && j==col) continue;
                                                else if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(2000);
                                glutSwapBuffers();

                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);

                                glutSwapBuffers();
                                
                                mainHeading();
                                generateNodes();

                                glutSwapBuffers();

                                //generating white edges
                                for(i=0; i<rows; i++){
                                        for(j=0; j<rows; j++){
                                                if(graph[i][j]!=0){
                                                        generateEdgesNotWorking(i, j, graph[i][j]);
                                                }
                                        }
                                }

                                glutSwapBuffers();

                                Sleep(1000);
                                glutSwapBuffers();
                        }
                }
}

void generateEdgesNotWorking(int row, int col, int cost){

        glColor3f(1.0f, 1.0f, 1.0f);
                if (row == 0) // node 0
                {
                        if (col == 1) // node 1
                        {
                                glBegin(GL_LINES);
                                glVertex2f(-0.2f, 0.6f);
                                glVertex2f(0.2f, 0.6f);
                                glEnd();

                                glRasterPos2f(0.0f, 0.7f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }
                        }
                        else if (col == 2) // node 2
                        {
                                glBegin(GL_LINES);
                                glVertex2f(-0.3f, 0.5f);
                                glVertex2f(-0.5f, 0.3f);
                                glEnd();
                                glRasterPos2f(-0.5f, 0.4f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }
                        }
                        else if (col == 3) // node 3
                        {

                                glBegin(GL_LINES);
                                glVertex2f(-0.3f, 0.5f);
                                glVertex2f(0.4f, 0.3f);
                                glEnd();
                                glRasterPos2f(-0.15f, 0.46f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }
                        }
                        else if (col == 4) // node 4
                        {
                                glBegin(GL_LINES);
                                glVertex2f(-0.3f, 0.5f);
                                glVertex2f(-0.3f, -0.1f);
                                glEnd();
                                glRasterPos2f(-0.3f, 0.3f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }
                        }
                        else if (col == 5) // node 5
                        {
                                glBegin(GL_LINES);
                                glVertex2f(-0.3f, 0.5f);
                                glVertex2f(0.2f, -0.1f);
                                glEnd();
                                glRasterPos2f(-0.1f, 0.3f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }
                        }
                }
                else if (row == 1) // node 1
                {
                        if (col == 2) // node 2
                        {
                                glBegin(GL_LINES);
                                glVertex2f(0.3f, 0.5f);
                                glVertex2f(-0.5f, 0.3f);
                                glEnd();
                                glRasterPos2f(0.1f, 0.5f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }
                        }
                        else if (col + 1 == 4) // node 4
                        {
                                glBegin(GL_LINES);
                                glVertex2f(0.3f, 0.5f);
                                glVertex2f(0.5f, 0.3f);
                                glEnd();
                                glRasterPos2f(0.5f, 0.4f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }
                        }
                        else if (col + 1 == 5) // node 5
                        {
                                glBegin(GL_LINES);
                                glVertex2f(0.3f, 0.5f);
                                glVertex2f(-0.3f, -0.1f);
                                glEnd();
                                glRasterPos2f(0.05f, 0.3f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }
                        }
                        else if (col + 1 == 6) // node 6
                        {
                                glBegin(GL_LINES);
                                glVertex2f(0.3f, 0.5f);
                                glVertex2f(0.3f, -0.1f);
                                glEnd();
                                glRasterPos2f(0.25f, 0.25f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }
                        }
                }
                else if (row + 1 == 3) // node 3
                {
                        if (col + 1 == 4) // node 4
                        {
                                glBegin(GL_LINES);
                                glVertex2f(-0.4f, 0.2f);
                                glVertex2f(0.4f, 0.2f);
                                glEnd();
                                glRasterPos2f(-0.2f, 0.15f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }
                        }
                        else if (col + 1 == 5) // node 5
                        {
                                glBegin(GL_LINES);
                                glVertex2f(-0.5f, 0.1f);
                                glVertex2f(-0.3f, -0.1f);
                                glEnd();
                                glRasterPos2f(-0.5f, -0.1f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }
                        }
                        else if (col + 1 == 6) // node 6
                        {
                                glBegin(GL_LINES);
                                glVertex2f(-0.5f, 0.1f);
                                glVertex2f(0.3f, -0.1f);
                                glEnd();
                                glRasterPos2f(-0.05f, 0.0f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }
                        }
                }
                else if (row + 1 == 4) // node 4
                {
                        if (col + 1 == 5) // node 5
                        {
                                glBegin(GL_LINES);
                                glVertex2f(0.5f, 0.1f);
                                glVertex2f(-0.3f, -0.1f);
                                glEnd();
                                glRasterPos2f(0.2f, 0.05f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }
                        }
                        else if (col + 1 == 6) // node 6
                        {
                                glBegin(GL_LINES);
                                glVertex2f(0.5f, 0.1f);
                                glVertex2f(0.3f, -0.1f);
                                glEnd();
                                glRasterPos2f(0.5f, -0.1f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }
                        }
                }
                else if (row + 1 == 5) // node 5
                {
                        if (col + 1 == 6) // node 6
                        {
                                glBegin(GL_LINES);
                                glVertex2f(-0.2f, -0.2f);
                                glVertex2f(0.2f, -0.2f);
                                glEnd();
                                glRasterPos2f(0.0f, -0.3f);
                                string str = to_string(cost);
                                for (char c : str)
                                {
                                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                                }
                        }
                }
}
void generateComponents()
{
        mainHeading();
        generateNodes();

        glutSwapBuffers();
}

void reshape(int w, int h)
{
        glutInitWindowPosition(0, 0);
        glutInitWindowSize(700, 700);
}

int main(int argc, char **argv)
{
        // currently in model view matrix

        cout<<"Enter graph upto 6 nodes:"<<endl;
        cout<<"Enter your size : "<<endl;
        scanf("%d", &rows);

        vector<int> temp;

        cout<<endl<<"Enter graph : "<<endl;

        for(i=0; i<rows; i++){
                int value;
                for(j=0; j<rows; j++){
                        cin>>value;
                        temp.push_back(value);
                }
                graph.push_back(temp);
                temp.clear();
        }
        

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB);

        glutInitWindowPosition(0, 0);
        glutInitWindowSize(700, 700);

        glutCreateWindow("DIJKSTRA ALGORITHM");

        // background color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // to change colors
        glEnable(GL_COLOR_MATERIAL);

        glutDisplayFunc(generateComponents);

        glutSwapBuffers();
        glutReshapeFunc(reshape);

        glutMainLoop();

        return 0;
}