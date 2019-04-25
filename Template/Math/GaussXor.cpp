//�� 2 ȡģ�� 01 ������
namespace Gauss{
	static const int N = 2e3 + 10;
	//�� equ �����̣� var ����Ԫ�������������Ϊ equ ,����Ϊ [0..var]
	bitset<N> a[N]; //������� modif
	bool ok[N]; // ��Ǳ�Ԫ�Ƿ�ȷ�� 
	int x[N]; //�⼯
	int free[N], free_num; //һ��Ϸ����ɱ�Ԫ�����ö�����ɱ�Ԫ����ʹ�ã�
	//����ֵΪ -1 ��ʾ�޽⣬Ϊ 0 ��Ψһ�⣬���򷵻����ɱ�Ԫ����
	int Gauss(int equ, int var){
		int p, col, k; // k Ϊ����������
		fill_n(ok, var, 0); free_num = 0;
		fill_n(x, var, 0);
		for(k = 0, col = 0; k < equ && col < var; k++, col++){
			p = k; rep(i, k, equ) if (a[i][col]) {p = i; break;}
			if (p != k) swap(a[k], a[p]);
			if (!a[k][col]){
				k--; free[free_num++] = col;//��������ɱ�Ԫ
				continue;
			}
			rep(i, 0, equ) if (i != k && a[i][col]) a[i] ^= a[k];
		}
		rep(i, col, var) free[free_num++] = i;
		rep(i, k, equ) if (a[i][var]) return -1;
		if(k < var) {
			/*per(i, 0, k) {
				int num = 0;
				rep(j, 0, var) if(a[i][j]) {
					if (!num) p = j; num++;
				}
				if(num > 1) continue;
				ok[p] = 1; x[p] = a[i][var];
			}*/
			return var - k;//���ɱ�Ԫ����
		} 
		//Ψһ�⣬�ش�
		per(i, 0, var){
			bool t = a[i][var];
			rep(j, i+1, var) t ^= (a[i][j] && x[j]);
			x[i] = t;
		}
		return 0;
	}
}
