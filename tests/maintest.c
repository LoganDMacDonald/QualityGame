
#include<stdio.h>
#include<stdlib.h>
#include <check.h>
#include "../main.h"

START_TEST (testNewCoin){

//before test sets up 



printf("Starting testNewCoin\n");

fail_unless(1==1,"failure message");

/*
fail_unless(sum(3,2)==5, "sum function failure\n")
*/

}
END_TEST


int main(){
     Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, testNewCoin);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;


   return 0;
}