#ifndef MENU_H
#define MENU_H

#include "main.h"

/*
create the menu instance
when moving cursor, call moveCursor()
*/

/*####################################################################################################
    Menu::  DO NOT EDIT
####################################################################################################*/
class menu
{

public:
    menu(int rows) : mRows(rows) {}


    void printCursor();
    

    int getCursorPos()
    {
        return cursorPos;
    }

//direction macros for setCursorPos
#define UP 1
#define DOWN 0

    void moveCursor(bool direction)
{
    if (direction)
    {
        if (cursorPos < mRows-1)
            cursorPos++;
        else
            cursorPos = 0;
    }
    else
    {
        if (cursorPos > 0)
            cursorPos--;
        else
            cursorPos = mRows-1;
    }

    printCursor(); //could make it public for more flexibility
}
    void setCurrentPage(void current_page_print()) {
        currentPage = current_page_print;
    }

    void refreshPage()
    {
        currentPage();
    }

private:
    int mRows;
    int cursorPos;

    void (*currentPage)();
};

//Menu Instance
extern menu myMenu;



#endif  //MENU_H