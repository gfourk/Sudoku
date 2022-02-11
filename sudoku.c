/********************************************************************
 *  sudoku.c

 * Author: George fourkis
 * Date: 2/4/2009
 * Scope:

 * Sudoku solver/generator/checker
*********************************************************************/
#include "sudoku.h"

/* Read a sudoku grid from stdin and return an object Grid_T
   initialized to these values. The input has the format:

1 2 3 4 5 6 7 8 9
4 5 6 7 8 9 1 2 3
7 8 9 1 2 3 4 5 6
2 3 4 5 6 7 8 9 1
5 6 7 8 9 1 2 3 4
8 9 1 2 3 4 5 6 7
3 4 5 6 7 8 9 1 2
6 7 8 9 1 2 3 4 5
9 1 2 3 4 5 6 7 8

   Each number is followed by a space. Each line is terminated with
   \n. Values of 0 indicate empty grid cells.
*/
Grid_T sudoku_read(void)
{
	int i,j,k;
	Grid_T g;
	for(i=0; i<9; i++)scanf("%d %d %d %d %d %d %d %d %d\n",&g.elts[i][0].val,&g.elts[i][1].val,&g.elts[i][2].val
							  ,&g.elts[i][3].val,&g.elts[i][4].val,&g.elts[i][5].val
							  ,&g.elts[i][6].val,&g.elts[i][7].val,&g.elts[i][8].val);
	for(i=0; i< 9; i++)
	{
	for(j=0; j<9; j++)
	{
		if( (grid_read_value(g,i,j)) != 0 )
		{
		grid_clear_count(&g, i, j);
		for(k=0; k<10; k++)grid_clear_choice(&g,i,j,k);
		}
		else
		{
		grid_set_count(&g, i, j);
		for(k=0; k<10; k++)grid_set_choice(&g,i,j,k);
		}
	}
	}
	grid_clear_unique(&g);
	return g;
}


/* Print the sudoku puzzle defined by g to stream s in the same format
   as expected by sudoku_read(). */
void sudoku_print(FILE *s, Grid_T g)
{
	int i,j;
	for(i=0; i<9; i++)
	{
	for(j=0; j<9; j++)
	{
		fprintf(s,"%d ",(grid_read_value(g,i,j)) );
	}
	fprintf(s,"\n");
	}
	fprintf(s,"\n\n");
}


/* Print all row, col, sub-grid errors/conflicts found in puzzle g;
   some errors may be reported more than once. */
void sudoku_print_errors(Grid_T g)
{
	int i,j,k,m,n,c[9][9],b[9][9],gr[9],st[9],bl[9],grammes=0,sthles=0,blocks=0;
/*arxikopoiountai oi pinakes*/
	for(i=0; i<9; i++)
	{
/*oi pinakes gr,st,bl einai gia tin yparksh lathous stis grammes,sthles kai tetragwna*/ 
	gr[i]=0;
	st[i]=0;
	bl[i]=0;     
	for(j=0; j<9; j++)
	{
/*o pinakas c exei tis times tou sudokou*/
		c[i][j]=(grid_read_value(g,i,j));
/*o pinakas b exei ws grammes ta tertagwna tou c*/
		b[i][j]=0;
	}
	}

/*dhmiourgei pinaka b pou exei ws grammes ta tertagwna tou pinaka c*/
	n=0;
	for(m=0; m<9; m=m+3)
	{     
	for(k=0; k<9; k=k+3)
	{
		for(i=m; i<m+3; i++)
		{     
		for(j=k; j<k+3; j++)
		{         
			b[n/9][n%9]=c[i][j];
			n++;
		}
		}
	}
	}

/*elenxei gia lathh se grammes,sthles kai tertagwna*/
	for(i=0; i<9; i++)
	{     
	for(j=0; j<9; j++)
	{
		for(k=j+1; k<9; k++)
		{
		if(  (c[i][j]==c[i][k] && c[i][j]!=0) || c[i][k]<0 || c[i][j]<0 || c[i][k]>9 || c[i][j]>9)
		{
/*an yparxoun lathi stin i grammi tote i antisixi timi tou pinaka g ginetai 1*/
			printf("to c[%d][%d] einai %d kai to c[%d][%d] einai %d\n",i,j,c[i][j],i,k,c[i][k]);
			gr[i]=1;
		}
		if( (c[j][i]==c[k][i] && c[j][i]!=0) || c[j][i]<0 || c[k][i]<0 || c[j][i]>9 || c[k][i]>9)
		{
/*an yparxoun lathi stin i sthlh tote i antisixi timi tou pinaka s ginetai 1*/                                    
			st[i]=1;
		}
		if( (b[i][j]==b[i][k] && b[i][j]!=0) || b[i][j]<0 || b[i][k]<0 || b[i][j]>9 || b[i][k]>9)
		{
/*an yparxoun lathi sto i tetragwno tote i antisixi timi tou pinaka t ginetai 1*/                                
			bl[i]=1;
		}
		}
	}
	}
/*typwnontai ta lathi twn grammwn an yparxoun*/
	fprintf(stderr,"\n\n");
	for(i=0; i<9; i++)
	{
	if((gr[i]==1)&&(grammes==0))
	{  
		fprintf(stderr,"lathos grammes: ");
		grammes=-1;
	}
	if(gr[i]==1)fprintf(stderr,"%d ", i+1);
	if((grammes==-1)&&(i==8))fprintf(stderr,"\n");
	} 
/*typwnontai ta lathi twn sthlwn an yparxoun*/
	for(i=0; i<9; i++)
	{
	if((st[i]==1)&&(sthles==0))
	{  
		fprintf(stderr,"lathos sthles: ");
		sthles=-1;
	}
	if(st[i]==1)fprintf(stderr,"%d ", i+1);
	if((sthles==-1)&&(i==8))fprintf(stderr,"\n");
	} 
/*typwnontai ta lathi twn tetragwnwn an yparxoun*/
	for(i=0; i<9; i++)
	{
	if((bl[i]==1)&&(blocks==0))
	{  
		fprintf(stderr,"lathos tertagwna: ");
		blocks=-1;
	}
	if(bl[i]==1)fprintf(stderr,"%d ", i+1);
	if((blocks==-1)&&(i==8))fprintf(stderr,"\n");
	} 
/*an den yparxoun lathi typwnetai oti i eisodos einai swsti*/
	if(grammes==-1 || sthles==-1 || blocks==-1)
	{
	return;
	}                                   
	fprintf(stderr,"swsti eisodos\n");
}


/* Return true iff puzzle g is correct. */
int sudoku_is_correct(Grid_T g)
{
	int i,j,k,m,n,c[9][9],b[9][9],gr[9],st[9],bl[9],grammes=0,sthles=0,blocks=0;
/*arxikopoiountai oi pinakes*/
	for(i=0; i<9; i++)
	{
/*oi pinakes gr,st,bl einai gia tin yparksh lathous stis grammes,sthles kai tetragwna*/ 
	gr[i]=0;
	st[i]=0;
	bl[i]=0;     
	for(j=0; j<9; j++)
	{
/*o pinakas c exei tis times tou sudokou*/
		c[i][j]=(grid_read_value(g,i,j));
/*o pinakas b exei ws grammes ta tertagwna tou c*/
		b[i][j]=0;
	}
	}

/*dhmiourgei pinaka b pou exei ws grammes ta tertagwna tou pinaka c*/
	n=0;
	for(m=0; m<9; m=m+3)
	{     
	for(k=0; k<9; k=k+3)
	{
		for(i=m; i<m+3; i++)
		{     
		for(j=k; j<k+3; j++)
		{         
			b[n/9][n%9]=c[i][j];
			n++;
		}
		}
	}
	}

/*elenxei gia lathh se grammes,sthles kai tertagwna*/
	for(i=0; i<9; i++)
	{     
	for(j=0; j<9; j++)
	{
		for(k=j+1; k<9; k++)
		{
		if( (c[i][j]==c[i][k] && c[i][j]!=0) || c[i][k]<0 || c[i][j]<0 || c[i][k]>9 || c[i][j]>9 )
		{
/*an yparxoun lathi stin i grammi tote i antisixi timi tou pinaka g ginetai 1*/
			gr[i]=1;
		}
		if( (c[j][i]==c[k][i] && c[j][i]!=0) || c[j][i]<0 || c[k][i]<0 || c[j][i]>9 || c[k][i]>9 )
		{
/*an yparxoun lathi stin i sthlh tote i antisixi timi tou pinaka s ginetai 1*/                                    
			st[i]=1;
		}
		if( (b[i][j]==b[i][k] && b[i][j]!=0) || b[i][k]<0 || b[i][j]<0 || b[i][k]>9 || b[i][j]>9 )
		{
/*an yparxoun lathi sto i tetragwno tote i antisixi timi tou pinaka t ginetai 1*/                                
			bl[i]=1;
		}
		}
	}
	}
	for(i=0; i<9; i++)
	{
	if((gr[i]==1)&&(grammes==0)){ grammes=-1; break; }
	} 
	for(i=0; i<9; i++)
	{
	if((st[i]==1)&&(sthles==0)){ sthles=-1; break; }
	} 
	for(i=0; i<9; i++)
	{
	if((bl[i]==1)&&(blocks==0)){ blocks=-1; break; }
	} 
	if(grammes==-1 || sthles==-1 || blocks==-1)
	{
	return 0;
	}
	return 1;
}

static int sudoku_is_solved(Grid_T g)
{
	int i,j,k,m,n,c[9][9],b[9][9],gr[9],st[9],bl[9],grammes=0,sthles=0,blocks=0;
/*arxikopoiountai oi pinakes*/
	for(i=0; i<9; i++)
	{
/*oi pinakes gr,st,bl einai gia tin yparksh lathous stis grammes,sthles kai tetragwna*/ 
	gr[i]=0;
	st[i]=0;
	bl[i]=0;     
	for(j=0; j<9; j++)
	{
/*o pinakas c exei tis times tou sudokou*/
		c[i][j]=(grid_read_value(g,i,j));
/*o pinakas b exei ws grammes ta tertagwna tou c*/
		b[i][j]=0;
	}
	}

/*dhmiourgei pinaka b pou exei ws grammes ta tertagwna tou pinaka c*/
	n=0;
	for(m=0; m<9; m=m+3)
	{     
	for(k=0; k<9; k=k+3)
	{
		for(i=m; i<m+3; i++)
		{     
		for(j=k; j<k+3; j++)
		{         
			b[n/9][n%9]=c[i][j];
			n++;
		}
		}
	}
	}

/*elenxei gia lathh se grammes,sthles kai tertagwna*/
	for(i=0; i<9; i++)
	{     
	for(j=0; j<9; j++)
	{
		for(k=j+1; k<9; k++)
		{
		if( (c[i][j]==c[i][k]) || c[i][k]<1 || c[i][j]<1 || c[i][k]>9 || c[i][j]>9 )
		{
/*an yparxoun lathi stin i grammi tote i antisixi timi tou pinaka g ginetai 1*/
			gr[i]=1;
		}
		if( (c[j][i]==c[k][i]) || c[j][i]<1 || c[k][i]<1 || c[j][i]>9 || c[k][i]>9 )
		{
/*an yparxoun lathi stin i sthlh tote i antisixi timi tou pinaka s ginetai 1*/                                    
			st[i]=1;
		}
		if( (b[i][j]==b[i][k]) || b[i][k]<1 || b[i][j]<1 || b[i][k]>9 || b[i][j]>9 )
		{
/*an yparxoun lathi sto i tetragwno tote i antisixi timi tou pinaka t ginetai 1*/                                
			bl[i]=1;
		}
		}
	}
	}
	for(i=0; i<9; i++)
	{
	if((gr[i]==1)&&(grammes==0)){ grammes=-1; break; }
	} 
	for(i=0; i<9; i++)
	{
	if((st[i]==1)&&(sthles==0)){ sthles=-1; break; }
	} 
	for(i=0; i<9; i++)
	{
	if((bl[i]==1)&&(blocks==0)){ blocks=-1; break; }
	} 
	if(grammes==-1 || sthles==-1 || blocks==-1)
	{
	return 0;
	}
	return 1;
}

/* Sovle puzzle g and return the solved puzzle; if the puzzle has
   multiple solutions, return one of the possible solutions. */
Grid_T sudoku_solve(Grid_T new_g)
{
	Grid_T test;
	int j,k,m,flag=1,temp=0,start=0,row=0,column=0;

	if( !sudoku_is_correct(new_g) )return new_g;
	else if( sudoku_is_solved(new_g) )return new_g;
	while(flag==1)
	{
	flag=0;
	for(j=0; j<9; j++)
	{
	for(k=0; k<9; k++)
	{
		int row=0,column=0,index=0;
		if( (grid_read_value(new_g,j,k))!=0 )
		{
			for(m=0; m<10; m++)grid_clear_choice(&new_g,j,k,m);
			grid_clear_count(&new_g, j, k);
			continue;
		}
		else
		{
			for(m=0; m<10; m++)grid_set_choice(&new_g,j,k,m);
			grid_set_count(&new_g, j, k);
		}

		if(j>=0 && j<=2 && k>=0 && k<=2){row=0;column=0;}
		else if(j>=0 && j<=2 && k>=3 && k<=5){row=0;column=3;}
		else if(j>=0 && j<=2 && k>=6 && k<=8){row=0;column=6;}
		else if(j>=3 && j<=5 && k>=0 && k<=2){row=3;column=0;}
		else if(j>=3 && j<=5 && k>=3 && k<=5){row=3;column=3;}
		else if(j>=3 && j<=5 && k>=6 && k<=8){row=3;column=6;}
		else if(j>=6 && j<=8 && k>=0 && k<=2){row=6;column=0;}
		else if(j>=6 && j<=8 && k>=3 && k<=5){row=6;column=3;}
		else if(j>=6 && j<=8 && k>=6 && k<=8){row=6;column=6;}
		for(m=0; m<9; m++)
		{
			grid_clear_choice(&new_g, j, k, grid_read_value(new_g,j,m) );
			grid_clear_choice(&new_g, j, k, grid_read_value(new_g,m,k) );
		}
		for(m=0; m<9; m++)
		{
			grid_clear_choice(&new_g, j, k, grid_read_value(new_g, row+(m/3), column+(m%3)) );
		}
		for(m=1; m<=9; m++)
		{
			if( new_g.elts[j][k].choices.num[m]==1)
			{
				index=m;
			}
			else grid_eliminate_count(&new_g, j ,k);
		}
		if( (grid_read_count(new_g, j, k))==1 )
		{
			flag=1;
			grid_update_value(&new_g,j,k,index);
			if( !sudoku_is_correct(new_g) )return new_g;
			else if( sudoku_is_solved(new_g) )
			{
				grid_set_unique(&new_g);
				return new_g;
			}
		}
		if( (grid_read_count(new_g, j, k))==0 )return new_g;

	}/*end of for*/
	}/*end of for*/
	}/*end of while*/
	grid_clear_unique(&new_g);
	m=10;
	for(j=0; j<9; j++)
	{
	for(k=0; k<9; k++)
	{
		if( (grid_read_value(new_g,j,k))==0 && (grid_read_count(new_g, j, k)<m) )
		{
			m = grid_read_count(new_g, j, k);
			row = j;
			column = k;
		}
	}
	}

	start = rand()%9+1;

	for(temp=start; temp<start+9; temp++)
	{
	if(temp>9)m=temp%9;
	else m=temp%10;

	if( new_g.elts[row][column].choices.num[m]==1)
	{
		grid_update_value(&new_g,row,column,m);;
		test = new_g;
		test = sudoku_solve(test);

		if( sudoku_is_solved(test) )
		{
			grid_clear_unique(&test);
			return test;
		}
		grid_update_value(&new_g,row,column,0);
	}
	}
	return new_g;
}


/* Returns true if solution g, as returned by sudoku_solve, has a
   unique choice for each step (no backtracking required). (Note, g
   must have been computed with the use of sudoku_solve.) */
int sudoku_solution_is_unique(Grid_T g)
{
	return grid_read_unique(g);
}

static Grid_T sudoku_generate_complete(void)
{
	Grid_T g;
	int i=0,j=0,k=0;

	for(i=0; i< 9; i++)
	{
	for(j=0; j<9; j++)
	{
		grid_update_value(&g,i,j,0);
		grid_set_count(&g, i, j);
		for(k=0; k<10; k++)grid_set_choice(&g,i,j,k);
	}
	}
	grid_update_value(&g,0,0,(rand()%9+1) );
	grid_update_value(&g,1,3,(rand()%9+1) );
	grid_update_value(&g,2,6,(rand()%9+1) );
	grid_update_value(&g,3,1,(rand()%9+1) );
	grid_update_value(&g,4,4,(rand()%9+1) );
	grid_update_value(&g,5,7,(rand()%9+1) );
	grid_update_value(&g,6,2,(rand()%9+1) );
	grid_update_value(&g,7,5,(rand()%9+1) );
	grid_update_value(&g,8,8,(rand()%9+1) );
	grid_clear_unique(&g);

	g = sudoku_solve(g);

	return g;
}

/* Generate and return a sudoku puzzle with "approximately" nelts
   elements having non-0 value. The smaller nelts the harder may be to
   generate/solve the puzzle. For instance, nelts=81 should return a
   completed and correct puzzle. If unique=1 the puzzle must have a
   unique choice at each step of finding the solution. */
Grid_T sudoku_generate(int nelts, int unique)
{
	Grid_T g,new_g;
	int n=81,i,j,r,value,count=0;
	g=sudoku_generate_complete();
	if(unique==1)
	{
	while(nelts<n)
	{
		do{
			r = rand()%81;
			i = r/9;
			j = r%9;
		}while( (grid_read_value(g,i,j))==0 );

		value =(grid_read_value(g,i,j));
		grid_update_value(&g,i,j,0);
		new_g=sudoku_solve(g);
		if( sudoku_solution_is_unique(new_g) )
		{
			n--;
			count = 0;
		}
		else
		{
			grid_update_value(&g,i,j,value);
			count++;
		}
		if(count==100)return g;
	}
	}
	else
	{
	while(nelts<n)
	{
		do{
			r = rand()%81;
			i = r/9;
			j = r%9;
		}while( (grid_read_value(g,i,j))==0 );

		grid_update_value(&g,i,j,0);
		n--;
	}
	}
	return g;
}

int main(int argc,char *argv[])
{
	Grid_T g;
	srand(getpid());

	if(argc==1)
	{
	g=sudoku_read();
	sudoku_print(stderr,g);
	g = sudoku_solve(g);
	if(g.unique)fprintf(stderr,"Puzzle has a (unique choice) solution:\n");
	else if(!sudoku_is_solved(g) )fprintf(stderr,"Puzzle has not solution:\n");
	else fprintf(stderr,"Puzzle has a (multiple choice) solution:\n");
	sudoku_print(stdout,g);
	}
	else if(argc==2)
	{
	if(argv[1][0]=='-' && argv[1][1]=='c')
	{
		g=sudoku_read();
		sudoku_print(stderr,g);
		/*if( sudoku_is_correct(g) )sudoku_print(stderr,g);
		else*/ sudoku_print_errors(g);
	}
	else printf("Wrong input parameter\n");
	}
	else if(argc==3)
	{
	if(argv[1][0]=='-' && argv[1][1]=='g')
	{
		g = sudoku_generate(atoi(argv[2]),0);
		sudoku_print(stdout,g);
	}
	else printf("Wrong input parameter\n");
	}
	else if(argc==4)
	{
	if(argv[1][0]=='-' && argv[1][1]=='g' && argv[3][0]=='-' && argv[3][1]=='u')
	{
		g = sudoku_generate(atoi(argv[2]),1);
		sudoku_print(stdout,g);
	}
	else printf("Wrong input parameter\n");
	}
	return 0;
}

