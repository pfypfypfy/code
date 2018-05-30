#include<bits/stdc++.h>
#define ll long long

using namespace std;

ll k, a, b;
bool f[20][15][1600];
void Init() {
	for(int i = 0; i <= 9; ++i)
		f[1][i][i * i] = 1;
	for(int i = 2; i <= 18; ++i) {
		for(int j = 0; j <= 1500; ++j)
			for(int k = 0; k <= 9; ++k) 
				for(int l = 0; l <= 9; ++l)
					if(j >= k * k)
						f[i][k][j] |= f[i - 1][l][j - k * k];		
	}
}
inline ll cal(ll x) {
	ll res = 0;
	while(x) {
		res += (x % 10) * (x % 10);
		x /= 10;
	}
	return res; 	
}
ll get(ll x) {
	if(x == 0) return 0;
	ll t = x;
	int shu[30], m = 0;
	ll cnt = 0;
	bool res[1600];
	memset(res, 0, sizeof res);
	while(x) {
		shu[++m] = x % 10;
		x /= 10;
	}
	for(int i = 0; i < shu[m]; ++i)
		for(int j = 1; j <= 1500; ++j)
			res[j] |= f[m][i][j];
	ll tot = shu[m] * shu[m];
	for(int i = m - 1; i >= 1; --i) {
		for(int j = 0; j < shu[i]; ++j)
			for(int k = 0; k + tot <= 1500; ++k)
				res[k + tot] |= f[i][j][k];
		tot += shu[i] * shu[i];
	}
	for(int i = 1; i <= t / k&& i <= 1500; ++i)
		if(i == cal(i * k))
			++cnt;
	return cnt;
}
int main() {
	freopen("coffin.in","r",stdin);
	freopen("coffin.out","w",stdout);
	scanf("%lld%lld%lld", &k, &a, &b);
	Init();
	printf("%lld\n", get(b) - get(a - 1));
	return 0;
}
