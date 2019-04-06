/* Precence table 
*
*    id  +  -  *  /  $
* id  -  >  >  >  >  >
*  +  <  >  >  <  <  >
*  -  <  >  >  <  <  >
*  *  <  >  >  >  >  >
*  /  <  >  >  >  >  >
*  $  <  <  <  <  <  -
* 
*/

struct vec6 {
	char array[6];
	char operator[](const char c){
		switch (c)
		{
			case 'i':
				return array[0];
				break;
			case '+':
				return array[1];
				break;
			case '-':
				return array[2];
				break;
			case '*':
				return array[3];
				break;
			case '/':
				return array[4];
				break;
			case '$':
				return array[5];
				break;
		
			default:
				return 'e';
				break;
		}
	}
};
struct operator_table {
	union{
		char precedence[6][6];
		vec6 vector[6];
	};
	operator_table(){
		precedence[0][0] = '-', precedence[0][1] = '>', precedence[0][2] = '>', precedence[0][3] = '>', precedence[0][4] = '>', precedence[0][5] = '>';
		precedence[1][0] = '<', precedence[1][1] = '>', precedence[1][2] = '>', precedence[1][3] = '<', precedence[1][4] = '<', precedence[1][5] = '>';
		precedence[2][0] = '<', precedence[2][1] = '>', precedence[2][2] = '>', precedence[2][3] = '<', precedence[2][4] = '<', precedence[2][5] = '>';
		precedence[3][0] = '<', precedence[3][1] = '>', precedence[3][2] = '>', precedence[3][3] = '>', precedence[3][4] = '>', precedence[3][5] = '>';
		precedence[4][0] = '<', precedence[4][1] = '>', precedence[4][2] = '>', precedence[4][3] = '>', precedence[4][4] = '>', precedence[4][5] = '>';
		precedence[5][0] = '<', precedence[5][1] = '<', precedence[5][2] = '<', precedence[5][3] = '<', precedence[5][4] = '<', precedence[5][5] = '-';
	}
	vec6& operator[](const char c){
		switch (c)
		{
			case 'i':
				return vector[0];
				break;
			case '+':
				return vector[1];
				break;
			case '-':
				return vector[2];
				break;
			case '*':
				return vector[3];
				break;
			case '/':
				return vector[4];
				break;
			case '$':
				return vector[5];
				break;
		
			default:
				return vector[6];
				break;
		}
	}
};