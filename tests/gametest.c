#include "./Unity/src/unity.h"
#include "../main.h"



void test_inbounds(void)
{
	/*
	   expect inBounds to return true for all values from 0 to 9
	   for both x and y
	   */
	TEST_ASSERT_EQUAL(0,inBounds(-1,0));
	TEST_ASSERT_EQUAL(0,inBounds(-1,-1));
	TEST_ASSERT_EQUAL(0,inBounds(0,-1));


	for(int i =0; i < 10;i++){
		for(int j =0; j<10;j++){
			TEST_ASSERT_EQUAL(1,inBounds(i,j));  
		}
	}



}

void test_initialize_map(void){
	/*
	   expect map to initialize with walls displayed as such
	 **********
	 *WWW**WWW*
	 *W******W*
	 *W******W*
	 ****WW****
	 ****WW****
	 *W******W*
	 *W******W*
	 *WWW**WWW*
	 **********
	 */




	extern char map[10][10];

	char expected_map[10][10] = {
		{'*','*','*','*','*','*','*','*','*','*'},
		{'*','W','W','W','*','*','W','W','W','*'},
		{'*','W','*','*','*','*','*','*','W','*'},
		{'*','W','*','*','*','*','*','*','W','*'},
		{'*','*','*','*','W','W','*','*','*','*'},
		{'*','*','*','*','W','W','*','*','*','*'},
		{'*','W','*','*','*','*','*','*','W','*'},
		{'*','W','*','*','*','*','*','*','W','*'},
		{'*','W','W','W','*','*','W','W','W','*'},
		{'*','*','*','*','*','*','*','*','*','*'}};


	initialize_map();
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			TEST_ASSERT_EQUAL(expected_map[i][j],map[i][j]);  
		}
	}
}



void test_claimCoin(void){

	extern int score;
	extern char map[10][10];
	int counter = 0;

	initialize_map();

	for(int i =0;i<10;i++){
		for (int j=0;j<10;j++){
			if(map[i][j] == '0'){
				claimCoin(i,j);
				TEST_ASSERT_EQUAL(++counter,score); 
			}
			else{
				claimCoin(i,j);
				TEST_ASSERT_EQUAL(counter,score);
			}
		}
	}


}





int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_inbounds);
	RUN_TEST(test_initialize_map);
	RUN_TEST(test_claimCoin);
	//RUN_TEST(test_AverageThreeBytes_should_AverageHighValues);
	return UNITY_END();
}
