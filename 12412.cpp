#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;

#define N 1000
#define L 100
#define eps 1e-6

int n = 0;
char sid[N][L];
int cid[N];
char name[N][L];
int score[N][5];
bool rmd[N];

bool valid(int k) {
    for (int i = 0; i < k; ++i)
        if (!rmd[i] && strcmp(sid[i], sid[k]) == 0)
            return false;
    return true;
}

void add() {
    while (puts("Please enter the SID, CID, name and four scores. Enter 0 to "
                "finish."),
           scanf("%s", sid[n]), strcmp(sid[n], "0") != 0) {
        scanf("%d%s%d%d%d%d", &cid[n], name[n], &score[n][0], &score[n][1],
              &score[n][2], &score[n][3]);
        if (valid(n)) {
            score[n][4] = accumulate(score[n], score[n] + 4, 0);
            ++n;
        } else {
            puts("Duplicated SID.");
        }
    }
}

int rnk(int k) {
    int r = 0;
    for (int i = 0; i < n; ++i)
        if (!rmd[i] && score[i][4] > score[k][4])
            ++r;
    return r + 1;
}

void DQ(int isq) {
    char s[L];
    while (puts("Please enter SID or name. Enter 0 to finish."), scanf("%s", s),
           strcmp(s, "0") != 0) {
        int r = 0;
        for (int i = 0; i < n; ++i) {
            if (rmd[i])
                continue;
            if (strcmp(sid[i], s) == 0 || strcmp(name[i], s) == 0) {
                if (isq) {
                    printf("%d %s %d %s %d %d %d %d %d %.2lf\n", rnk(i), sid[i],
                           cid[i], name[i], score[i][0], score[i][1],
                           score[i][2], score[i][3], score[i][4],
                           score[i][4] / 4.0 + eps);
                } else {
                    rmd[i] = true;
                    ++r;
                }
            }
        }
        if (!isq)
            printf("%d student(s) removed.\n", r);
    }
}

double get_course_stat(int c, int s, int& passed, int& failed) {
    int total = 0;
    for (int i = 0; i < n; ++i) {
        if (rmd[i])
            continue;
        if (c == 0 || cid[i] == c) {
            total += score[i][s];
            if (score[i][s] >= 60)
                ++passed;
            else
                ++failed;
        }
    }
    return (double)total / (passed + failed);
}

void get_overrall_stat(int c, int cnt[]) {
    for (int i = 0; i < n; ++i) {
        if (rmd[i])
            continue;
        if (c == 0 || cid[i] == c) {
            ++cnt[count_if(score[i], score[i] + 4,
                           bind2nd(greater_equal<int>(), 60))];
        }
    }
}

void stat() {
    int c;

    static const char* course_name[] = {
        "Chinese", "Mathematics", "English", "Programming"
    };
    
    puts("Please enter class ID, 0 for the whole statistics.");
    scanf("%d", &c);
    for (int i = 0; i < 4; ++i) {
        int passed = 0, failed = 0;
        double avg = get_course_stat(c, i, passed, failed);
        printf("%s\n", course_name[i]);
        printf("Average Score: %.2lf\n", avg + eps);
        printf("Number of passed students: %d\n", passed);
        printf("Number of failed students: %d\n", failed);
        puts("");
    }
    int cnt[5] = {0};
    get_overrall_stat(c, cnt);
    puts("Overall:");
    printf ("Number of students who passed all subjects: %d\n", cnt[4]);  
    printf ("Number of students who passed 3 or more subjects: %d\n", cnt[4] + cnt[3]);  
    printf ("Number of students who passed 2 or more subjects: %d\n", cnt[4] + cnt[3] + cnt[2]);  
    printf ("Number of students who passed 1 or more subjects: %d\n", cnt[4] + cnt[3] + cnt[2] + cnt[1]);  
    printf ("Number of students who failed all subjects: %d\n", cnt[0]);  
    puts("");
}

void print_menu() {
    printf("Welcome to Student Performance Management System (SPMS).\n\n"
           "1 - Add\n"
           "2 - Remove\n"
           "3 - Query\n"
           "4 - Show ranking\n"
           "5 - Show Statistics\n"
           "0 - Exit\n\n");
}

int main() {
    int choice;
    while (print_menu(), scanf("%d", &choice), choice != 0) {
        if (choice == 1)
            add();
        else if (choice == 2)
            DQ(0);
        else if (choice == 3)
            DQ(1);
        else if (choice == 4)
            puts("Showing the ranklist hurts students' self-esteem. Don't do that.");
        else if (choice == 5)
            stat();
    }
    return 0;
}
