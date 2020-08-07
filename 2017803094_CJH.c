#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int mwin(); //로그인 전
int signin(); //로그인 하는 거
int sup(); //회원가입
int sout(); //메인에서 로그인 후 키
int mwinaflogin(); //메인에서 로그인 후
int plinfo(); //로그인 후 - 회원정보
int game(); //게임화면
int wd(); //탈퇴화면

char GID[100]; //id 저장할 전역변수
char PWD[100]; //pwd 저장할 전역변수
char *ptrG = GID;
char *ptrG2 = PWD;

int signin() { //로그인 화면
    curs_set(1);
    WINDOW *window1;
    WINDOW *window2;

    initscr();

    window1 = newwin(18,80, 0, 0);
    window2 = newwin(6, 80, 18, 0);

    wbkgd(window1, COLOR_PAIR(1));
    wbkgd(window2, COLOR_PAIR(2));

    wattron(window1, A_BOLD);
    mvwprintw(window1, 6, 35, "SIGN IN");
    wattroff(window1, A_BOLD);

    mvwprintw(window1, 10, 24, "PASSWORD : ");
    mvwprintw(window1, 8, 30, "ID : ");

    mvwprintw(window2, 3, 20, "SIGN IN");
    mvwprintw(window2, 3, 55, "BACK");

    wrefresh(window2);

    int k = 0; //커서
    
    char id[100];
    mvwscanw(window1, 8, 35, "%s", id);
    wrefresh(window2);
    char pwd[100];
    mvwscanw(window1, 10, 35, "%s", pwd);
    wrefresh(window2);

    curs_set(0);
    wattron(window2, A_REVERSE);
    mvwprintw(window2, 3, 20, "SIGN IN");
    wattroff(window2, A_REVERSE);
    wrefresh(window2);

    int key;
    keypad(window2, TRUE);
    while(1) {
        
        key = wgetch(window2);
        switch(key) {
            case KEY_RIGHT:
                if(k==0) {
                    mvwprintw(window2, 3, 20, "SIGN IN");
                    wattron(window2, A_REVERSE);
                    mvwprintw(window2, 3, 55, "BACK");
                    wattroff(window2, A_REVERSE);
                    k++;
                    refresh();
                }
                else if(k==1) {
                    mvwprintw(window2, 3, 55, "BACK");
                    wattron(window2, A_REVERSE);
                    mvwprintw(window2, 3, 20, "SIGN IN");
                    wattroff(window2, A_REVERSE);
                    k--;
                    refresh();
                }
            break;
            case KEY_LEFT:
                if(k==0) {
                    mvwprintw(window2, 3, 20, "SIGN IN");
                    wattron(window2, A_REVERSE);
                    mvwprintw(window2, 3, 55, "BACK");
                    wattroff(window2, A_REVERSE);
                    k++;
                    refresh();
                }
                else if(k==1) {
                    mvwprintw(window2, 3, 55, "BACK");
                    wattron(window2, A_REVERSE);
                    mvwprintw(window2, 3, 20, "SIGN IN");
                    wattroff(window2, A_REVERSE);
                    k--;
                    refresh();
                }
            break;
            case 10:
                if(k==0) {
                    ptrG = id;
                    ptrG2 = pwd;
                    chdir("userinfo");
                    int s; //mkdir 반환 값 받을 변수
                    s = mkdir(ptrG, 0755);
                    if(s == -1) { //이미 존재하는 경우 즉, id를 똑같은 것을 썼다.
                        chdir(ptrG);
                        int s2; //mkdir 두번째 반환 값 받을 변수
                        s2 = mkdir(ptrG2, 0755);
                        if (s2 == -1) { // 비밀 번호 까지 맞췄음
                            chdir("..");
                            chdir("..");
                            erase();
                            refresh();
                            wrefresh(window2);
                            mwinaflogin();
                        }
                        else if (s2 == 0) { //아이디는 맞았는데 비밀번호가 틀려서 비밀번호 디렉토리가 새로 생김
                            mvwprintw(window2, 5, 0, ">>> Password Error! Try Again! (Press any key ...)");
                            rmdir(ptrG2);
                            chdir("..");
                            int key2;
                            key2 = wgetch(window2);
                            erase();
                            refresh();
                            wrefresh(window2);
                            signin();
                        }
                    }
                    else if(s == 0) { 
                        mvwprintw(window2, 5, 0, ">>> %s is not exist in DB! Try Again! (Please any key...)", ptrG);
                        rmdir(ptrG);
                        int key2;
                        key2 = wgetch(window2);
                        erase();
                        refresh();
                        wrefresh(window2);
                        signin();
                    }
                }
                else if(k==1) {
                    erase();
                    refresh();
                    mwin();
                }
        }

    }

    refresh();
    wrefresh(window1);
    wrefresh(window2);

    keypad(stdscr, TRUE);
    keypad(window1, TRUE);
 
    refresh();
    getch();
    endwin();
    return 0;

}

int sup() { //signup 화면
    curs_set(1);
    WINDOW *window1;
    WINDOW *window2;

    initscr();

    window1 = newwin(18,80, 0, 0);
    window2 = newwin(6, 80, 18, 0);

    wbkgd(window1, COLOR_PAIR(1));
    wbkgd(window2, COLOR_PAIR(2));

    wattron(window1, A_BOLD);
    mvwprintw(window1, 6, 35, "SIGN UP");
    wattroff(window1, A_BOLD);

    mvwprintw(window1, 10, 24, "PASSWORD : ");
    mvwprintw(window1, 8, 30, "ID : ");

    mvwprintw(window2, 3, 20, "SIGN UP");
    mvwprintw(window2, 3, 55, "BACK");

    wrefresh(window2);

    int k = 0; 
    
    char id[100];
    mvwscanw(window1, 8, 35, "%s", id);
    wrefresh(window2);

    char pwd[100];
    mvwscanw(window1, 10, 35, "%s", pwd);
    wrefresh(window2);

    curs_set(0);
    wattron(window2, A_REVERSE);
    mvwprintw(window2, 3, 20, "SIGN UP");
    wattroff(window2, A_REVERSE);
    wrefresh(window2);

    int key;
    keypad(window2, TRUE);
    while(1) {
        
        key = wgetch(window2);
        switch(key) {
            case KEY_RIGHT:
                if(k==0) {
                    mvwprintw(window2, 3, 20, "SIGN UP");
                    wattron(window2, A_REVERSE);
                    mvwprintw(window2, 3, 55, "BACK");
                    wattroff(window2, A_REVERSE);
                    k++;
                    refresh();
                }
                else if(k==1) {
                    mvwprintw(window2, 3, 55, "BACK");
                    wattron(window2, A_REVERSE);
                    mvwprintw(window2, 3, 20, "SIGN UP");
                    wattroff(window2, A_REVERSE);
                    k--;
                    refresh();
                }
            break;
            case KEY_LEFT:
                if(k==0) {
                    mvwprintw(window2, 3, 20, "SIGN UP");
                    wattron(window2, A_REVERSE);
                    mvwprintw(window2, 3, 55, "BACK");
                    wattroff(window2, A_REVERSE);
                    k++;
                    refresh();
                }
                else if(k==1) {
                    mvwprintw(window2, 3, 55, "BACK");
                    wattron(window2, A_REVERSE);
                    mvwprintw(window2, 3, 20, "SIGN UP");
                    wattroff(window2, A_REVERSE);
                    k--;
                    refresh();
                }
            break;
            case 10:
                if(k==0) {
                    // char *ptrG = GID;
                    ptrG = id;
                    // char *ptrG2 = PWD;
                    ptrG2 = pwd;
                    chdir("userinfo");
                    int s; //mkdir 반환 값 받을 변수
                    s = mkdir(ptrG, 0755);
                    if(s == 0) {
                        mkdir(ptrG, 0755);
                        chdir(ptrG);
                        mkdir(ptrG2, 0755);
                        chdir("..");
                        chdir("..");
                        mvwprintw(window2, 5, 0, ">>> Welcome to OTHELLO World! (Press any key...)");
                        int key2;
                        key2 = wgetch(window2);
                        erase();
                        refresh();
                        wrefresh(window2);
                        mwin();
                    }
                    else if(s == -1) {
                        mvwprintw(window2, 5, 0, ">>> %s has already exist in DB! (Please any key...)", ptrG);
                        int key2;
                        key2 = wgetch(window2);
                        erase();
                        refresh();
                        wrefresh(window2);
                        sup();
                    }
                }
                else if(k==1) {
                    erase();
                    refresh();
                    mwin();
                }
        }

    }

    refresh();
    wrefresh(window1);
    wrefresh(window2);

    keypad(stdscr, TRUE);
    keypad(window1, TRUE);
    
    refresh();
    getch();
    endwin();
    return 0;

}


int mwin() { //가장 첫 화면
    WINDOW *window1;
    WINDOW *window2;

    initscr();

    if(has_colors() == FALSE) {
        puts("Terminal does not support colors!");
        endwin();
        return 1;
    } else {
        start_color();
        init_pair(1, COLOR_BLUE, COLOR_WHITE);
        init_pair(2, COLOR_WHITE, COLOR_BLUE);
    }

    window1 = newwin(18,80, 0, 0);
    window2 = newwin(6, 80, 18, 0);

    wbkgd(window1, COLOR_PAIR(1));
    wbkgd(window2, COLOR_PAIR(2));

    mvwprintw(window1, 6, 27, "System SoftWare Practice");
    wattron(window1, A_BOLD);
    mvwprintw(window1, 8, 35, "OTHELLO");
    wattroff(window1, A_BOLD);
    mvwprintw(window1, 13, 65, "2017803094");
    mvwprintw(window1, 15, 65, "JiHoon Choi");

    wattron(window2, A_REVERSE);
    mvwprintw(window2, 3, 10, "SIGN IN");
    wattroff(window2, A_REVERSE);
    mvwprintw(window2, 3, 40, "SIGN UP");
    mvwprintw(window2, 3, 65, "EXIT");
    curs_set(0);

    refresh();
    wrefresh(window1);
    wrefresh(window2);

    keypad(stdscr, TRUE);
    keypad(window2, TRUE);
    
    int key;
    
    int k = 0;
    while(1) {
        key = wgetch(window2);
        switch(key) {
            case KEY_RIGHT:
                if(k==0) {
                    mvwprintw(window2, 3, 10, "SIGN IN");
                    wattron(window2, A_REVERSE);
                    mvwprintw(window2, 3, 40, "SIGN UP");
                    wattroff(window2, A_REVERSE);
                    k++;
                    refresh();
                    wrefresh(window2);
                }
                
                else if(k==1) {
                    mvwprintw(window2, 3, 40, "SIGN UP");
                    wattron(window2, A_REVERSE);
                    mvwprintw(window2, 3, 65, "EXIT");
                    wattroff(window2, A_REVERSE);
                    k++;
                    refresh();
                    
                }

                else if(k==2) {
                    mvwprintw(window2, 3, 65, "EXIT");
                    wattron(window2, A_REVERSE);
                    mvwprintw(window2, 3, 10, "SIGN IN");
                    wattroff(window2, A_REVERSE);
                    k = 0;
                    refresh();
                }
            break;
            case KEY_LEFT:
                if(k==0) {
                    mvwprintw(window2, 3, 10, "SIGN IN");
                    wattron(window2, A_REVERSE);
                    mvwprintw(window2, 3, 65, "EXIT");
                    wattroff(window2, A_REVERSE);
                    k = 2;
                    refresh();
                    wrefresh(window2);
                }
                
                else if(k==1) {
                    mvwprintw(window2, 3, 40, "SIGN UP");
                    wattron(window2, A_REVERSE);
                    mvwprintw(window2, 3, 10, "SIGN IN");
                    wattroff(window2, A_REVERSE);
                    k--;
                    refresh();
                    
                }

                else if(k==2) {
                    mvwprintw(window2, 3, 65, "EXIT");
                    wattron(window2, A_REVERSE);
                    mvwprintw(window2, 3, 40, "SIGN UP");
                    wattroff(window2, A_REVERSE);
                    k--;
                    refresh();
                }
            break;
            case 10:
                if(k==0) {
                    erase();
                    endwin();
                    refresh();
                    wrefresh(window2);
                    signin();
                }
                else if(k==1) {
                    erase();
                    refresh();
                    wrefresh(window2);
                    sup();
                }
                else if(k==2) {
                    endwin();
                    exit(0);
                }
            break;
        }

    }

    getch();
    wrefresh(window1);
    wrefresh(window2);
    endwin();
    return 0;
}

int mwinaflogin() { //로그인 후 화면
    WINDOW *window1;
    WINDOW *window2;

    initscr();

    window1 = newwin(18,80, 0, 0);
    window2 = newwin(6, 80, 18, 0);

    wbkgd(window1, COLOR_PAIR(1));
    wbkgd(window2, COLOR_PAIR(2));
   
    mvwprintw(window1, 6, 30, "Player ID : %s", ptrG);
    
    wattron(window2, A_REVERSE);
    mvwprintw(window2, 3, 10, "PLAY");
    wattroff(window2, A_REVERSE);
    mvwprintw(window2, 3, 40, "SIGN OUT");
    mvwprintw(window2, 3, 65, "WITHDRAWAL");

    refresh();
    wrefresh(window1);
    wrefresh(window2);

    refresh();
    wrefresh(window1);
    wrefresh(window2);

    keypad(stdscr, TRUE);
  
    int k = 0;

    int key;
    keypad(window2, TRUE);
    while(1) {
        key = wgetch(window2);
        switch(key) {
            case KEY_RIGHT:
                if(k==0) {
                    mvwprintw(window2, 3, 10, "PLAY");
                    wattron(window2, A_REVERSE);
                    mvwprintw(window2, 3, 40, "SIGN OUT");
                    wattroff(window2, A_REVERSE);
                    k++;
                    refresh();
                    wrefresh(window2);
                }
                
                else if(k==1) {
                    mvwprintw(window2, 3, 40, "SIGN OUT");
                    wattron(window2, A_REVERSE);
                    mvwprintw(window2, 3, 65, "WITHDRAWAL");
                    wattroff(window2, A_REVERSE);
                    k++;
                    refresh();
                    
                }

                else if(k==2) {
                    mvwprintw(window2, 3, 65, "WITHDRAWAL");
                    wattron(window2, A_REVERSE);
                    mvwprintw(window2, 3, 10, "PLAY");
                    wattroff(window2, A_REVERSE);
                    k = 0;
                    refresh();
                }
            break;
            case KEY_LEFT:
                if(k==0) {
                    mvwprintw(window2, 3, 10, "PLAY");
                    wattron(window2, A_REVERSE);
                    mvwprintw(window2, 3, 65, "WITHDRAWAL");
                    wattroff(window2, A_REVERSE);
                    k = 2;
                    refresh();
                    wrefresh(window2);
                }
                
                else if(k==1) {
                    mvwprintw(window2, 3, 40, "SIGN OUT");
                    wattron(window2, A_REVERSE);
                    mvwprintw(window2, 3, 10, "PLAY");
                    wattroff(window2, A_REVERSE);
                    k--;
                    refresh();
                    
                }

                else if(k==2) {
                    mvwprintw(window2, 3, 65, "WITHDRAWAL");
                    wattron(window2, A_REVERSE);
                    mvwprintw(window2, 3, 40, "SIGN OUT");
                    wattroff(window2, A_REVERSE);
                    k--;
                    refresh();
                }
            break;
            case 10:
                if(k==0) {
                    erase();
                    refresh();
                    wrefresh(window2);
                    plinfo();
                }
                else if(k==1) {
                    erase();
                    refresh();
                    wrefresh(window2);
                    mwin();
                }
                else if(k==2) {
                    erase();
                    refresh();
                    wrefresh(window2);
                    wd();
                }
            break;
        }

    }

    return 0;

}

int plinfo() { //회원정보 출력화면
    WINDOW *window1;
    WINDOW *window2;

    initscr();

    window1 = newwin(18,80, 0, 0);
    window2 = newwin(6, 80, 18, 0);

    wbkgd(window1, COLOR_PAIR(1));
    wbkgd(window2, COLOR_PAIR(2));
   
    mvwprintw(window1, 8, 30, "Player ID : %s", ptrG);

    wattron(window1, A_BOLD);
    mvwprintw(window1, 10, 35, "STATISTICS");
    wattroff(window1, A_BOLD);

    int win;
    int lose;
    int all;
    double winrate;
    win = 8;
    lose = 2;
    all = win + lose;
    winrate = (double) win / (double) all * 100.0;

    mvwprintw(window1, 12, 25, "WIN : %d / LOSE : %d (%.2f%)", win, lose, winrate);
    
    wattron(window2, A_REVERSE);
    mvwprintw(window2, 3, 39, "OK");
    wattroff(window2, A_REVERSE);

    refresh();
    wrefresh(window1);
    wrefresh(window2);

    keypad(stdscr, TRUE);
    
    int k = 0;

    //noecho();
    int key;
    keypad(window2, TRUE);
    while(1) {
        key = wgetch(window2);
        switch(key) {
            case 10:
                if(k==0) {
                    erase();
                    refresh();
                    game();
                }
            break;
        }

    }
    return 0;

}

int game() { //게임화면
    WINDOW *window1;
    WINDOW *window2;

    initscr();

    if(has_colors() == FALSE) {
        puts("Terminal does not support colors!");
        endwin();
        return 1;
    } else {
        start_color();
        init_pair(1, COLOR_BLUE, COLOR_WHITE);
        init_pair(2, COLOR_WHITE, COLOR_BLUE);
    }

    refresh();

    window1 = newwin(24, 60, 0, 0);
    window2 = newwin(24, 20, 0, 60);

    wbkgd(window1, COLOR_PAIR(1));
    wbkgd(window2, COLOR_PAIR(2));

    mvwprintw(window1, 6, 15, "+---+---+---+---+---+---+");
    mvwprintw(window1, 7, 15, "|");
    mvwprintw(window1, 7, 19, "|");
    mvwprintw(window1, 7, 23, "|");
    mvwprintw(window1, 7, 27, "|");
    mvwprintw(window1, 7, 31, "|");
    mvwprintw(window1, 7, 35, "|");
    mvwprintw(window1, 7, 39, "|");
    mvwprintw(window1, 8, 15, "+---+---+---+---+---+---+");
    mvwprintw(window1, 9, 15, "|");
    mvwprintw(window1, 9, 19, "|");
    mvwprintw(window1, 9, 23, "|");
    mvwprintw(window1, 9, 27, "|");
    mvwprintw(window1, 9, 31, "|");
    mvwprintw(window1, 9, 35, "|");
    mvwprintw(window1, 9, 39, "|");
    mvwprintw(window1, 10, 15, "+---+---+---+---+---+---+");
    mvwprintw(window1, 11, 15, "|");
    mvwprintw(window1, 11, 19, "|");
    mvwprintw(window1, 11, 23, "|");
    mvwprintw(window1, 11, 27, "|");
    mvwprintw(window1, 11, 31, "|");
    mvwprintw(window1, 11, 35, "|");
    mvwprintw(window1, 11, 39, "|");
    mvwprintw(window1, 12, 15, "+---+---+---+---+---+---+");
    mvwprintw(window1, 13, 15, "|");
    mvwprintw(window1, 13, 19, "|");
    mvwprintw(window1, 13, 23, "|");
    mvwprintw(window1, 13, 27, "|");
    mvwprintw(window1, 13, 31, "|");
    mvwprintw(window1, 13, 35, "|");
    mvwprintw(window1, 13, 39, "|");
    mvwprintw(window1, 14, 15, "+---+---+---+---+---+---+");
    mvwprintw(window1, 15, 15, "|");
    mvwprintw(window1, 15, 19, "|");
    mvwprintw(window1, 15, 23, "|");
    mvwprintw(window1, 15, 27, "|");
    mvwprintw(window1, 15, 31, "|");
    mvwprintw(window1, 15, 35, "|");
    mvwprintw(window1, 15, 39, "|");
    mvwprintw(window1, 16, 15, "+---+---+---+---+---+---+");
    mvwprintw(window1, 17, 15, "|");
    mvwprintw(window1, 17, 19, "|");
    mvwprintw(window1, 17, 23, "|");
    mvwprintw(window1, 17, 27, "|");
    mvwprintw(window1, 17, 31, "|");
    mvwprintw(window1, 17, 35, "|");
    mvwprintw(window1, 17, 39, "|");
    mvwprintw(window1, 18, 15, "+---+---+---+---+---+---+");

    refresh();
    wrefresh(window1);
    wrefresh(window2);

    wattron(window1, A_REVERSE);
    mvwprintw(window1, 11, 24, " O ");
    wattroff(window1, A_REVERSE);
    mvwprintw(window1, 11, 28, " X ");
    mvwprintw(window1, 13, 24, " X ");
    mvwprintw(window1, 13, 28, " O ");
    mvwprintw(window2, 16, 13, "E");
    wattron(window2, A_UNDERLINE);
    mvwprintw(window2, 16, 14, "X");
    wattroff(window2, A_UNDERLINE);
    mvwprintw(window2, 16, 15, "IT");

    refresh();
    wrefresh(window1);
    wrefresh(window2);

    int key;
    keypad(window1, TRUE);
    //noecho();
    refresh();
    wrefresh(window1);
    wrefresh(window2);
    int x = 0;
    int y = 0;

    while(1) {
        
        key = wgetch(window1);
        wrefresh(window2);
        
        switch(key) {
            case KEY_RIGHT:
                if(x == 8 && y == -8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 7, 16, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 7, 20, "   ");
                    wattroff(window1, A_REVERSE);
                    y+=4;
                    refresh();
                }
                else if(x == 8 && y == -4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 7, 20, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 7, 24, "   ");
                    wattroff(window1, A_REVERSE);
                    y+=4;
                    refresh();
                }
                else if(x == 8 && y == 0) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 7, 24, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 7, 28, "   ");
                    wattroff(window1, A_REVERSE);
                    y+=4;
                    refresh();
                }
                else if(x == 8 && y == 4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 7, 28, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 7, 32, "   ");
                    wattroff(window1, A_REVERSE);
                    y+=4;
                    refresh();
                }
                else if(x == 8 && y == 8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 7, 32, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 7, 36, "   ");
                    wattroff(window1, A_REVERSE);
                    y+=4;
                    refresh();
                }
                //8, 12일때는 오른쪽 안됨
                if(x == 4 && y == -8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 9, 16, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 9, 20, "   ");
                    wattroff(window1, A_REVERSE);
                    y+=4;
                    refresh();
                }
                else if(x == 4 && y == -4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 9, 20, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 9, 24, "   ");
                    wattroff(window1, A_REVERSE);
                    y+=4;
                    refresh();
                }
                else if(x == 4 && y == 0) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 9, 24, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 9, 28, "   ");
                    wattroff(window1, A_REVERSE);
                    y+=4;
                    refresh();
                }
                else if(x == 4 && y == 4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 9, 28, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 9, 32, "   ");
                    wattroff(window1, A_REVERSE);
                    y+=4;
                    refresh();
                }
                else if(x == 4 && y == 8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 9, 32, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 9, 36, "   ");
                    wattroff(window1, A_REVERSE);
                    y+=4;
                    refresh();
                }
                //y가 12일때는 오른쪽 안됨
                else if(x == 0 && y == -8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 11, 16, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 11, 20, "   ");
                    wattroff(window1, A_REVERSE);
                    y += 4;
                    refresh();
                }
                else if(x == 0 && y == -4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 11, 20, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 11, 24, " O ");
                    wattroff(window1, A_REVERSE);
                    y += 4;
                    refresh();
                }
                else if(x == 0 && y == 0) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 11, 28, " X ");
                    wattroff(window1, A_REVERSE);
                    y += 4;
                    refresh();
                }
                else if(x == 0 && y == 4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 11, 32, "   ");
                    wattroff(window1, A_REVERSE);
                    y += 4;
                    refresh();
                }
                else if(x == 0 && y == 8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 11, 32, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 11, 36, "   ");
                    wattroff(window1, A_REVERSE);
                    y += 4;
                    refresh();
                }
                //y12일때는 안됨
                else if(x == -4 && y == -8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 13, 16, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 13, 20, "   ");
                    wattroff(window1, A_REVERSE);
                    y += 4;
                    refresh();
                }
                else if(x == -4 && y == -4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 13, 20, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 13, 24, " X ");
                    wattroff(window1, A_REVERSE);
                    y += 4;
                    refresh();
                }
                else if(x == -4 && y == 0) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 13, 28, " O ");
                    wattroff(window1, A_REVERSE);
                    y += 4;
                    refresh();
                }
                else if(x == -4 && y == 4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 13, 32, "   ");
                    wattroff(window1, A_REVERSE);
                    y += 4;
                    refresh();
                }
                else if(x == -4 && y == 8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 13, 32, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 13, 36, "   ");
                    wattroff(window1, A_REVERSE);
                    y += 4;
                    refresh();
                }
                //y12일때는 안됨
                else if(x == -8 && y == -8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 15, 16, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 15, 20, "   ");
                    wattroff(window1, A_REVERSE);
                    y += 4;
                    refresh();
                }
                else if(x == -8 && y == -4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 15, 20, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 15, 24, "   ");
                    wattroff(window1, A_REVERSE);
                    y += 4;
                    refresh();
                }
                else if(x == -8 && y == 0) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 15, 24, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 15, 28, "   ");
                    wattroff(window1, A_REVERSE);
                    y += 4;
                    refresh();
                }
                else if(x == -8 && y == 4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 15, 28, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 15, 32, "   ");
                    wattroff(window1, A_REVERSE);
                    y += 4;
                    refresh();
                }
                else if(x == -8 && y == 8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 15, 32, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 15, 36, "   ");
                    wattroff(window1, A_REVERSE);
                    y += 4;
                    refresh();
                }
                //y12일때는 안됨
                else if(x == -12 && y == -8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 17, 16, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 17, 20, "   ");
                    wattroff(window1, A_REVERSE);
                    y += 4;
                    refresh();
                }
                else if(x == -12 && y == -4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 17, 20, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 17, 24, "   ");
                    wattroff(window1, A_REVERSE);
                    y += 4;
                    refresh();
                }
                else if(x == -12 && y == 0) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 17, 24, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 17, 28, "   ");
                    wattroff(window1, A_REVERSE);
                    y += 4;
                    refresh();
                }
                else if(x == -12 && y == 4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 17, 28, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 17, 32, "   ");
                    wattroff(window1, A_REVERSE);
                    y += 4;
                    refresh();
                }
                else if(x == -12 && y == 8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 17, 32, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 17, 36, "   ");
                    wattroff(window1, A_REVERSE);
                    y += 4;
                    refresh();
                }
                //y12일때는 안됨
            break;
            
            case KEY_LEFT:
                if(x == 8 && y == -4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 7, 20, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 7, 16, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }
                else if(x == 8 && y == 0) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 7, 24, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 7, 20, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }
                else if(x == 8 && y == 4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 7, 28, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 7, 24, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }
                else if(x == 8 && y == 8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 7, 32, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 7, 28, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }
                else if(x == 8 && y == 12) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 7, 36, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 7, 32, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }

                else if(x == 4 && y == -4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 9, 20, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 9, 16, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }
                else if(x == 4 && y == 0) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 9, 24, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 9, 20, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }
                else if(x == 4 && y == 4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 9, 28, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 9, 24, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }
                else if(x == 4 && y == 8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 9, 32, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 9, 28, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }
                else if(x == 4 && y == 12) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 9, 36, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 9, 32, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }

                else if(x == 0 && y == -4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 11, 20, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 11, 16, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }
                else if(x == 0 && y == 0) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 11, 20, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }
                else if(x == 0 && y == 4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 11, 24, " O ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }
                else if(x == 0 && y == 8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 11, 32, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 11, 28, " X ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }
                else if(x == 0 && y == 12) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 11, 36, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 11, 32, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }

                else if(x == -4 && y == -4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 13, 20, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 13, 16, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }
                else if(x == -4 && y == 0) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 13, 20, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }
                else if(x == -4 && y == 4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 13, 24, " X ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }
                else if(x == -4 && y == 8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 13, 32, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 13, 28, " O ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }
                else if(x == -4 && y == 12) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 13, 36, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 13, 32, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }

                else if(x == -8 && y == -4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 15, 20, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 15, 16, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }
                else if(x == -8 && y == 0) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 15, 24, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 15, 20, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }
                else if(x == -8 && y == 4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 15, 28, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 15, 24, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }
                else if(x == -8 && y == 8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 15, 32, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 15, 28, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }
                else if(x == -8 && y == 12) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 15, 36, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 15, 32, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }

                else if(x == -12 && y == -4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 17, 20, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 17, 16, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }
                else if(x == -12 && y == 0) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 17, 24, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 17, 20, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }
                else if(x == -12 && y == 4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 17, 28, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 17, 24, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }
                else if(x == -12 && y == 8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 17, 32, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 17, 28, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }
                else if(x == -12 && y == 12) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 17, 36, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 17, 28, "   ");
                    wattroff(window1, A_REVERSE);
                    y -= 4;
                    refresh();
                }
            break;
            
            case KEY_UP:
                if(x == 4 && y == -8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 9, 16, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 7, 16, "   ");
                    wattroff(window1, A_REVERSE);
                    x += 4;
                    refresh();
                }
                else if(x == 0 && y == -8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 11, 16, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 9, 16, "   ");
                    wattroff(window1, A_REVERSE);
                    x+=4;
                    refresh();
                }
                else if(x == -4 && y == -8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 13, 16, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 11, 16, "   ");
                    wattroff(window1, A_REVERSE);
                    x+=4;
                    refresh();
                }
                else if(x == -8 && y == -8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 15, 16, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 13, 16, "   ");
                    wattroff(window1, A_REVERSE);
                    x+=4;
                    refresh();
                }
                else if(x == -12 && y == -8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 17, 16, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 15, 16, "   ");
                    wattroff(window1, A_REVERSE);
                    x+=4;
                    refresh();
                }

                else if(x == 4 && y == -4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 9, 20, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 7, 20, "   ");
                    wattroff(window1, A_REVERSE);
                    x += 4;
                    refresh();
                }
                else if(x == 0 && y == -4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 11, 20, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 9, 20, "   ");
                    wattroff(window1, A_REVERSE);
                    x+=4;
                    refresh();
                }
                else if(x == -4 && y == -4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 13, 20, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 11, 20, "   ");
                    wattroff(window1, A_REVERSE);
                    x+=4;
                    refresh();
                }
                else if(x == -8 && y == -4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 15, 20, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 13, 20, "   ");
                    wattroff(window1, A_REVERSE);
                    x+=4;
                    refresh();
                }
                else if(x == -12 && y == -4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 17, 20, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 15, 20, "   ");
                    wattroff(window1, A_REVERSE);
                    x+=4;
                    refresh();
                }

                else if(x == 4 && y == 0) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 9, 24, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 7, 24, "   ");
                    wattroff(window1, A_REVERSE);
                    x += 4;
                    refresh();
                }
                else if (x == 0 && y == 0) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 9, 24, "   ");
                    wattroff(window1, A_REVERSE);
                    x += 4;
                    refresh();
                }
                else if (x == -4 && y == 0) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 11, 24, " O ");
                    wattroff(window1, A_REVERSE);
                    x += 4;
                    refresh();
                }
                else if (x == -8 && y == 0) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 15, 24, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 13, 24, " X ");
                    wattroff(window1, A_REVERSE);
                    x += 4;
                    refresh();
                }
                else if(x == -12 && y == 0) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 17, 24, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 15, 24, "   ");
                    wattroff(window1, A_REVERSE);
                    x += 4;
                    refresh();
                }

                else if(x == 4 && y == 4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 9, 28, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 7, 28, "   ");
                    wattroff(window1, A_REVERSE);
                    x += 4;
                    refresh();
                }
                else if (x == 0 && y == 4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 9, 28, "   ");
                    wattroff(window1, A_REVERSE);
                    x += 4;
                    refresh();
                }
                else if (x == -4 && y == 4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 11, 28, " X ");
                    wattroff(window1, A_REVERSE);
                    x += 4;
                    refresh();
                }
                else if (x == -8 && y == 4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 15, 28, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 13, 28, " O ");
                    wattroff(window1, A_REVERSE);
                    x += 4;
                    refresh();
                }
                else if(x == -12 && y == 4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 17, 28, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 15, 28, "   ");
                    wattroff(window1, A_REVERSE);
                    x += 4;
                    refresh();
                }

                else if(x == 4 && y == 8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 9, 32, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 7, 32, "   ");
                    wattroff(window1, A_REVERSE);
                    x += 4;
                    refresh();
                }
                else if(x == 0 && y == 8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 11, 32, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 9, 32, "   ");
                    wattroff(window1, A_REVERSE);
                    x+=4;
                    refresh();
                }
                else if(x == -4 && y == 8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 13, 32, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 11, 32, "   ");
                    wattroff(window1, A_REVERSE);
                    x+=4;
                    refresh();
                }
                else if(x == -8 && y == 8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 15, 32, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 13, 32, "   ");
                    wattroff(window1, A_REVERSE);
                    x+=4;
                    refresh();
                }
                else if(x == -12 && y == 8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 17, 32, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 15, 32, "   ");
                    wattroff(window1, A_REVERSE);
                    x+=4;
                    refresh();
                }

                else if(x == 4 && y == 12) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 9, 36, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 7, 36, "   ");
                    wattroff(window1, A_REVERSE);
                    x += 4;
                    refresh();
                }
                else if(x == 0 && y == 12) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 11, 36, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 9, 36, "   ");
                    wattroff(window1, A_REVERSE);
                    x+=4;
                    refresh();
                }
                else if(x == -4 && y == 12) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 13, 36, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 11, 36, "   ");
                    wattroff(window1, A_REVERSE);
                    x+=4;
                    refresh();
                }
                else if(x == -8 && y == 12) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 15, 36, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 13, 36, "   ");
                    wattroff(window1, A_REVERSE);
                    x+=4;
                    refresh();
                }
                else if(x == -12 && y == 12) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 17, 36, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 15, 36, "   ");
                    wattroff(window1, A_REVERSE);
                    x+=4;
                    refresh();
                }
            break;
            case KEY_DOWN:
                if(x == 8 && y == -8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 7, 16, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 9, 16, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }
                else if(x == 4 && y == -8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 9, 16, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 11, 16, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }
                else if(x == 0 && y == -8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 11, 16, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 13, 16, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }
                else if(x == -4 && y == -8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 13, 16, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 15, 16, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }
                else if(x == -8 && y == -8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 15, 16, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 17, 16, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }

                else if(x == 8 && y == -4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 7, 20, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 9, 20, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }
                else if(x == 4 && y == -4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 9, 20, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 11, 20, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }
                else if(x == 0 && y == -4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 11, 20, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 13, 20, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }
                else if(x == -4 && y == -4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 13, 20, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 15, 20, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }
                else if(x == -8 && y == -4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 15, 20, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 17, 20, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }

                else if(x == 8 && y == 0) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 7, 24, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 9, 24, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }
                else if(x == 4 && y == 0) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 9, 24, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 11, 24, " O ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }
                else if(x == 0 && y == 0) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 13, 24, " X ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }
                else if(x == -4 && y == 0) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 15, 24, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }
                else if(x == -8 && y == 0) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 15, 24, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 17, 24, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }

                else if(x == 8 && y == 4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 7, 28, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 9, 28, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }
                else if(x == 4 && y == 4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 9, 28, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 11, 28, " X ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }
                else if(x == 0 && y == 4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 13, 28, " O ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }
                else if(x == -4 && y == 4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 15, 28, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }
                else if(x == -8 && y == 4) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 15, 28, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 17, 28, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }

                else if(x == 8 && y == 8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 7, 32, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 9, 32, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }
                else if(x == 4 && y == 8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 9, 32, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 11, 32, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }
                else if(x == 0 && y == 8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 11, 32, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 13, 32, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }
                else if(x == -4 && y == 8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 13, 32, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 15, 32, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }
                else if(x == -8 && y == 8) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 15, 32, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 17, 32, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }

                else if(x == 8 && y == 12) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 7, 36, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 9, 36, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }
                else if(x == 4 && y == 12) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 9, 36, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 11, 36, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }
                else if(x == 0 && y == 12) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 11, 36, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 13, 36, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }
                else if(x == -4 && y == 12) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 13, 36, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 15, 36, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }
                else if(x == -8 && y == 12) {
                    mvwprintw(window1, 11, 24, " O ");
                    mvwprintw(window1, 11, 28, " X ");
                    mvwprintw(window1, 13, 24, " X ");
                    mvwprintw(window1, 13, 28, " O ");
                    mvwprintw(window1, 15, 36, "   ");
                    wattron(window1, A_REVERSE);
                    mvwprintw(window1, 17, 36, "   ");
                    wattroff(window1, A_REVERSE);
                    x-=4;
                    refresh();
                }
            break;
            noecho();
            case 120:
                
                refresh();
                wattron(window2, A_REVERSE);
                mvwprintw(window2, 16, 13, "E");
                wattroff(window2, A_REVERSE);
                wattron(window2, A_UNDERLINE | A_REVERSE);
                mvwprintw(window2, 16, 14, "X");
                wattroff(window2, A_UNDERLINE | A_REVERSE);
                wattron(window2, A_REVERSE);
                mvwprintw(window2, 16, 15, "IT");
                wattroff(window2, A_REVERSE);
                // echo();
                refresh();
                wrefresh(window1);
                wrefresh(window2);
            break; //while문 빠져나간다.
        }
    }

    echo();

    int key2;
    key2 = keypad(window2, TRUE);
    switch(key2) {
        if(key2 == 10) {
            erase();
            refresh();
            mwinaflogin();
        }
    }
    
    

    getch();
    wrefresh(window1);
    wrefresh(window2);
    endwin();
    return 0;

}

int wd() {
    curs_set(1);
    WINDOW *window1;
    WINDOW *window2;

    initscr();

    window1 = newwin(18,80, 0, 0);
    window2 = newwin(6, 80, 18, 0);

    wbkgd(window1, COLOR_PAIR(1));
    wbkgd(window2, COLOR_PAIR(2));

    wattron(window1, A_BOLD);
    mvwprintw(window1, 6, 35, "WITHDRAWAL");
    wattroff(window1, A_BOLD);

    mvwprintw(window1, 10, 24, "PASSWORD : ");
    mvwprintw(window1, 8, 28, "PLAYER ID : %s", ptrG);

    mvwprintw(window2, 3, 18, "WITHDRAWAL");
    mvwprintw(window2, 3, 55, "BACK");

    wrefresh(window2);

    int k = 0; 
    
    char pwd[100];
    mvwscanw(window1, 10, 35, "%s", pwd);
    wrefresh(window2);

    curs_set(0);
    wattron(window2, A_REVERSE);
    mvwprintw(window2, 3, 18, "WITHDRAWAL");
    wattroff(window2, A_REVERSE);
    // refresh();
    // wrefresh(window1);
    wrefresh(window2);

    int key;
    keypad(window2, TRUE);
    while(1) {
        
        key = wgetch(window2);
        switch(key) {
            case KEY_RIGHT:
                if(k==0) {
                    mvwprintw(window2, 3, 18, "WITHDRAWAL");
                    wattron(window2, A_REVERSE);
                    mvwprintw(window2, 3, 55, "BACK");
                    wattroff(window2, A_REVERSE);
                    k++;
                    refresh();
                }
                else if(k==1) {
                    mvwprintw(window2, 3, 55, "BACK");
                    wattron(window2, A_REVERSE);
                    mvwprintw(window2, 3, 18, "WITHDRAWAL");
                    wattroff(window2, A_REVERSE);
                    k--;
                    refresh();
                }
            break;
            case KEY_LEFT:
                if(k==0) {
                    mvwprintw(window2, 3, 18, "WITHDRAWAL");
                    wattron(window2, A_REVERSE);
                    mvwprintw(window2, 3, 55, "BACK");
                    wattroff(window2, A_REVERSE);
                    k++;
                    refresh();
                }
                else if(k==1) {
                    mvwprintw(window2, 3, 55, "BACK");
                    wattron(window2, A_REVERSE);
                    mvwprintw(window2, 3, 18, "WITHDRAWAL");
                    wattroff(window2, A_REVERSE);
                    k--;
                    refresh();
                }
            break;
            case 10:
                if(k==0) {
                    ptrG2 = pwd;
                    chdir("userinfo");
                    chdir(ptrG);
                    int i; //mkdir 반환 값 받을 변수
                    i = mkdir(ptrG2, 0755);
                    if (i == -1) { //pwd가 맞아서 열리지 않는 경우, 계정을 삭제해야 한다.
                        mvwprintw(window2, 5, 0, ">>> %s deleted in DB! (Press any key...)", ptrG);
                        rmdir(ptrG2);
                        chdir("..");
                        rmdir(ptrG);
                        chdir("..");
                        int key2;
                        key2 = wgetch(window2);
                        erase();
                        refresh();
                        mwin();
                    }
                    else if (i == 0) { //pwd가 맞지 않아서 열리는 경우, rmdir 필요하고, 오류메시지 출력
                        mvwprintw(window2, 5, 0, ">>> %s doesn't match passwrod! Try Again! (Press any key ...)", ptrG);
                        rmdir(ptrG2);
                        int key2;
                        key2 = wgetch(window2);
                        erase();
                        refresh();
                        wd();

                    }
                }
                else if(k==1) {
                    erase();
                    refresh();
                    mwinaflogin();
                }
        }

    }

    refresh();
    wrefresh(window1);
    wrefresh(window2);

    keypad(stdscr, TRUE);
    keypad(window1, TRUE);
    
    refresh();
    getch();
    endwin();
    return 0;
}

int main(int argc, char const *argv[]) {
    noecho();
    mkdir("userinfo",0755);
    mwin();
    
}