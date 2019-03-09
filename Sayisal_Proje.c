/*
1.Kök Bulma Yöntemleri
	1.1.Grafik Yöntemi  
	1.2.Yarıya Bölme Yöntemi  (yapildi)
	1.3.Regula False Yöntemi  (yapildi)
	1.4.Newton Raphson Yöntemi (yapildi)
2.Matris İşlemleri
	2.1.Matrisnin inversinin alınması  (yapildi)
3.Doğrusal Denklem Takımlarının Çözümü
	3.1.Gauss Eleminasyon (Yapiliyor)(yarim birakildi yanlis calisiyor(Segmentation fault hatasi alindi)) 
	3.2 Gauss Jordan Eleminasyon yöntemlerinden birini 
4.Nümerik Integral
	4.1.Trapez yöntemi(Yapiliyor)
	4.2.Simpson Yöntemi
5.Nümerik Türev
*/

#include <stdio.h>
#include <stdlib.h>

struct Eleman{
	int derece;
	int katsayi;
};

struct Polinom{
	int eleman_sayisi;
	struct Eleman eleman[16];
};

struct Polinom pol;
struct Polinom turevPol;

void menu(void);
float fonkHesapla(float x,struct Polinom polinom);
void polFunc(void );
void yariya_bolme(void);
void regula_false(void);
void newton_raphson(void);
void matris_invers_al(void);
void gauss_eliminasyon(void);
void trapez(void);
int main(int argc, char const *argv[])
{
	char x,y;
/*
	do
	{	*/
		menu();

		printf("x:");
		scanf("%c",&x);
	
		printf("y:");
		scanf("\n%c",&y);

		switch(x)
		{
			case '1':
				switch(y)
				{
					case '1':
						break;
					case '2':
						yariya_bolme();
						break;
					case '3':
						regula_false();
						break;
					case '4':
						newton_raphson();
						break;
				}	
			case '2':
				switch(y)
				{
					case '1':
						matris_invers_al();
						break;
				}
			case '3':
				switch(y)
				{
					case '1':
						gauss_eliminasyon();
						break;
					case '2':
						break;
				}
			case '4':
				switch(y)
				{
					case '1':
						trapez();
						break;
					case '2':
						break;
				}
			case '5':
				switch(y)
				{
					case '1':
						break;
				}
			break;
		}

	//}while();
	return 0;
}

void menu(void)
{
	printf("1.Kök Bulma Yöntemleri\n"
				"\t1.1.Grafik Yöntemi\n"
				"\t1.2.Yarıya Bölme Yöntemi\n"
				"\t1.3.Regula False Yöntemi\n"
				"\t1.4.Newton Raphson Yöntemi\n"
			"2.Matris İşlemleri\n"
				"\t2.1.Matrisnin inversinin alınması\n"
			"3.Doğrusal Denklem Takımlarının Çözümü\n"
				"\t3.1.Gauss Eleminasyon \n"
				"\t3.2.Gauss Jordan Eleminasyon\n"
			"4.Nümerik Integral\n"
				"\t4.1.Trapez yöntemi\n"
				"\t4.2.Simpson Yöntemi\n"
			"5.0.Nümerik Türev\n");
	printf("Calistirmak istediginiz program icin x ve y degerlerini giriniz.\n");
	printf("Mesela \nTrapez Yontemi icin x=4 ve y=1\nNOT:Numerik Turev icin x=5 y=0 giriniz.\n");

}

float fonkHesapla(float x,struct Polinom polinom)
{
	int i,j;
	float y=0,y0=1;
	for(i=0;i<polinom.eleman_sayisi;i++)
	{
		for(j=0;j<(polinom.eleman[i]).derece;j++)
		{
			y0*=x;
		}
		y0*=polinom.eleman[i].katsayi;
		y+=y0;
		y0=1;
	}
	return y;
}


void polFunc(void)
{
	int sayi,i;
	printf("Polinomdaki eleman sayisini giriniz:");
	scanf("%d",&sayi);
	pol.eleman_sayisi=sayi;
	for(i=0;i<pol.eleman_sayisi;i++)
	{
		printf("\n%d.ci elemanin derecesini giriniz:",i+1);
		scanf("%d",&sayi);
		(pol.eleman[i]).derece=sayi;
		printf("%d.ci elemanin katsayisini giriniz:",i+1);
		scanf("%d",&sayi);
		(pol.eleman[i]).katsayi=sayi;
	}
}

void yariya_bolme(void)
{
	float xl,xr,xm,yl,yr,ym,epsilon;

	polFunc();

	printf("xL(xleft) degerini giriniz:");
	scanf("%f",&xl);
	printf("xR(xright) degerini giriniz:");
	scanf("%f",&xr);
	printf("Epsilon degerini giriniz:");
	scanf("%f",&epsilon);	

	yl=fonkHesapla(xl,pol);
	yr=fonkHesapla(xr,pol);
	
	if((yl<0 && yr>0 ) || (yl>0 && yr<0) )
	{
		printf("Bu aralikta kok vardir.\n");
		printf("%-10s%-10s%-10s%-10s%-10s%-10s\n","xl","xr","yl","yr","xm","ym");
		do
		{
			xm=(xl+xr)/2;
			ym=fonkHesapla(xm,pol);
			yl=fonkHesapla(xl,pol);
			yr=fonkHesapla(xr,pol);
			printf("%-10f%-10f%-10f%-10f%-10f%-10f\n",xl,xr,yl,yr,xm,ym);

			if((yl<0 && ym>0 ) || (yl>0 && ym<0))
			{
				xr=xm;
			}

			if((yr<0 && ym>0 ) || (yr>0 && ym<0))
			{
				xl=xm;
			}
		}while(ym>0?(ym>=epsilon):((-1)*ym>=epsilon));
		printf("%-10f%-10f%-10f%-10f%-10f%-10f\n",xl,xr,yl,yr,xm,ym);
	}
	else
	{
		printf("Bu aralikta kok yoktur ve ya bu yontemle bulunamaz.");
	}
}

void regula_false(void)
{
	float xl,xr,xm,yl,yr,ym,epsilon;

	polFunc();

	printf("xL(xleft) degerini giriniz:");
	scanf("%f",&xl);
	printf("xR(xright) degerini giriniz:");
	scanf("%f",&xr);
	printf("Epsilon degerini giriniz:");
	scanf("%f",&epsilon);	

	yl=fonkHesapla(xl,pol);
	yr=fonkHesapla(xr,pol);
	
	if((yl<0 && yr>0 ) || (yl>0 && yr<0) )
	{
		printf("Bu aralikta kok vardir.\n");
		printf("%-10s%-10s%-10s%-10s%-10s%-10s\n","xl","xr","yl","yr","xm","ym");
		do
		{
			xm=(xl*yr-xr*yl)/(yr-yl);
			ym=fonkHesapla(xm,pol);
			yl=fonkHesapla(xl,pol);
			yr=fonkHesapla(xr,pol);
			printf("%-10f%-10f%-10f%-10f%-10f%-10f\n",xl,xr,yl,yr,xm,ym);

			if((yl<0 && ym>0 ) || (yl>0 && ym<0))
			{
				xr=xm;
			}

			if((yr<0 && ym>0 ) || (yr>0 && ym<0))
			{
				xl=xm;
			}
		}while(ym>0?(ym>=epsilon):((-1)*ym>=epsilon));
		printf("%-10f%-10f%-10f%-10f%-10f%-10f\n",xl,xr,yl,yr,xm,ym);
	}
	else
	{
		printf("Bu aralikta kok yoktur ve ya bu yontemle bulunamaz.");
	}
	
}

void newton_raphson(void)
{
	float x0,y0,yT0,x1=0,epsilon;
	int i,j=0;
	polFunc();

	printf("Baslamak x0 degerini giriniz:");
	scanf("%f",&x0);
	printf("Epsilon degerini giriniz:");
	scanf("%f",&epsilon);

	turevPol.eleman_sayisi=pol.eleman_sayisi;
	for(i=0;i<pol.eleman_sayisi;i++)
	{
		if((pol.eleman[i]).derece!=0)
		{
			(turevPol.eleman[j]).derece=(pol.eleman[i]).derece-1;
			(turevPol.eleman[j]).katsayi=(pol.eleman[i]).derece*(pol.eleman[i]).katsayi;
			j++;
		}
		else
		{
			turevPol.eleman_sayisi-=1;
		}
	}
	printf("%-12s%-12s%-12s%-12s\n","x1","x0","y0","y0Turev");

	printf("\neleman:%d\n 1.derece %d\t1.katsayi %d\n2.derece %d\t2.katsayi %d\n",turevPol.eleman_sayisi,
	turevPol.eleman[0].derece,turevPol.eleman[0].katsayi,
	turevPol.eleman[1].derece,turevPol.eleman[1].katsayi);
	getchar();
	getchar();
	y0=fonkHesapla(x0,pol);
	yT0=fonkHesapla(x0,turevPol);
	while(y0>0?(y0>=epsilon):((-1)*y0>=epsilon)){
		x1=x0-y0/yT0;		
		printf("%-12f%-12f%-12f%-12f\n",x1,x0,y0,yT0);
		x0=x1;
		y0=fonkHesapla(x0,pol);
		yT0=fonkHesapla(x0,turevPol);
	}
}
void matris_invers_al(void)
{
	int flag,n,i,j,k;
	float **matris;
	float **adj;

	printf("NxN-lik bir matris gireceksiniz.Ilk once n degerini girmeniz gerekiyor.");
	printf("\nN degerini giriniz:");scanf("%d",&n);

	matris=(float **)malloc(n*sizeof(float *));
	adj=(float **)malloc(n*sizeof(float *));

	for(i=0;i<n;i++)
	{
		matris[i]=(float *)malloc(n*sizeof(float));
		adj[i]=(float *)malloc(n*sizeof(float));
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("matris[%d][%d]. elemanini giriniz:",i+1,j+1);
			scanf("%f",&matris[i][j]);
			((i==j)?(adj[i][j]=1):(adj[i][j]=0));
		}
	}
	flag=1;
	for(i=0;i<n && flag ;i++)
	{
		if(matris[i][i]==0)
		{
			int gi=0;
			while(gi<n && matris[gi][i]==0)
			{
				gi++;
			}
		
			if(gi<n)
			{
				for(j=0;j<n;j++)
				{
					float tmp=adj[gi][j];
					adj[gi][j]=adj[i][j];
					adj[i][j]=tmp;
					tmp=matris[gi][j];
					matris[gi][j]=matris[i][j];
					matris[i][j]=tmp;
				}
			}
			else
			{
				flag=0;
			}
		}
		if(flag)
		{
			float tmp=matris[i][i];
			for(j=0;j<n;j++)
			{
				matris[i][j]/=tmp;
				adj[i][j]/=tmp;
			}
			for(k=0;k<n;k++)
			{
				if(k!=i)
				{
					tmp=(-1)*matris[k][i];
					for(j=0;j<n && tmp!=0 ;j++)
					{
						matris[k][j]+=tmp*matris[i][j];
						adj[k][j]+=tmp*adj[i][j];
					}
				}
			}
		}

	}

	i=0;
	while(flag && i<n)
	{
		if(matris[i][i]!=1)
		{
			printf("Matrisin inversi yoktur.\n");
			flag=0;
		}
		i++;
	}
	if(flag)
	{
		printf("Matrisin inversi\n");
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				printf("%14f",adj[i][j]);
			}
			puts("");
		}
	}

}

void gauss_eliminasyon(void)
{
	int i,j,N;
	int k,count1,flag,cozulurmu;
	float **matris;
	float **anahtar;
	float **X;
	cozulurmu=1;
	printf("NxN-lik bir matris gireceksiniz.Ilk once n degerini girmeniz gerekiyor.");
	printf("\nN degerini giriniz:");scanf("%d",&N);

	matris=(float **)malloc(N*sizeof(float *));
	anahtar=(float **)malloc(1*sizeof(float *));
	X=(float **)malloc(1*sizeof(float *));
	for(i=0;i<N;i++)
	{
		matris[i]=(float *)malloc(N*sizeof(float));
		anahtar[i]=(float *)malloc(1*sizeof(float));
		X[i]=(float *)malloc(1*sizeof(float));
	}

	printf("Matrisi giriniz");

	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			printf("Matris[%d][%d] degerini giriniz:",i+1,j+1);scanf("%f",&matris[i][j]);
		}
	}
	printf("\nAnahtar matrisini giriniz.\n");
	for(i=0;i<N;i++)
	{
		printf("Anahtar[%d] degerini giriniz:",i+1);scanf("%f",&anahtar[0][i]);
	}

	yaz(N,matris,anahtar);
	for (i = 0; cozulurmu && i < N; ++i)
	{
		if(matris[i][i]!=0 && cozulurmu )
		{
			for(j=i+1; j<N ; j++ )
			{
				for(k=i+1; k<N ;k++)
				{
					matris[i][k]/=matris[i][i];
				}
				anahtar[0][i]/=matris[i][i];
				matris[i][i]=1;
				yaz(N,matris,anahtar);
				flag=1;
				k=i+1;

				while(k<N && flag)
				{
					flag=1;
					if(matris[k][i]==0)
					{
						while(matris[k][i]==0 && k<N)
						{
							k++;
						}
						if(k=N)
						{
							flag=0;
						}
					}
					else
					{
						float tmp=matris[k][i]*(-1);
						for(count1=i;count1<N;count1++)
						{
							matris[k][count1]+=matris[i][count1]*tmp;
						}
						anahtar[0][k]+=anahtar[0][i]*tmp;
					}
					yaz(N,matris,anahtar);
					k++;
				}
			}
		}
		else
		{
			k=i+1;
			while(k<N && matris[k][i]==0)
			{
				k++;
			}
			if(k==N)
			{
				printf("Cozulemez\n");
				cozulurmu=0;
			}
			else
			{
				for(count1=i; count1<N;count1++)
				{
					float tmp=matris[i][count1];
					matris[i][count1]=matris[k][count1];
					matris[k][count1]=tmp;
				}
				float tmp=anahtar[0][i];
				anahtar[0][i]=anahtar[0][k];
				anahtar[0][k]=tmp;
			}
		}

	}
	yaz(N,matris,anahtar);
	if(cozulurmu)
	{
		anahtar[0][N-1]/=matris[N-1][N-1];
		matris[N-1][N-1]=1;
		yaz(N,matris,anahtar);

		//Xlari burda tapmaga baslayiriq

		for(i=0;i<N;i++)
		{
			X[0][i]=anahtar[0][i];
		}

		for(i=N-2;i>=0;i--)
		{
			for(j=i+1;j<N;j++)
			{
				X[0][i]-=matris[i][j]*X[0][j];
			}
		
		}
		printf("\n");
		for (j = 0; j < N; j++)
		{
			printf("x%d=%10f\n",j+1,X[0][j] );
		}
	}

}

void yaz(int N,float **A,float **C)
{
	int i,j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			printf("%12.6f",A[i][j] );
		}	
		printf(" || %12.6f\n",C[0][i]);
	}
	getchar();
	getchar();
}

void trapez(void)
{
	float x0,xN,deltaX;
	int N,i;
	printf("x degiskenin hangi araliklarda hesaplanacagini giriniz.\n");

	printf("Araligin minimum degeri:");scanf("%f",&x0);
	printf("Araligin maksimum degeri:");scanf("%f",&xN);

	printf("N degerini giriniz(Eger degeri sifir olarak girirseniz, N degiskeninin default degeri 6 olarak alinacaktir.):\n");scanf("%d",&N);

	if(N==0)
	{
		N=6;
	}

	deltaX=(xN-x0)/N;

	polFunc();




}