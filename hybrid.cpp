#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <bitset>
#include <math.h>
#include <algorithm>
#include <cstddef> 
#include <iterator>

using namespace std;

int size1; long long int size_table,k,m2,m1,n1,n3;
int gshare_index,bimodal_index;
string temp_branch_status;
string n2;
int mispredict_counter=0;

vector<int> gshare_table;
vector<int> bimodal_table;

string hex2bin(string addre_hex)
{
	
	int addre_bin;
	istringstream st(addre_hex);
	st>>hex>>addre_bin;
	
	bitset<24> bits(addre_bin);
	
	string address_binary(bits.to_string());
	return address_binary;
	
}

string extract_index_bits(string addre_binary,int temp_size)
{
	//cout<<temp_size<<endl;
	return addre_binary.substr((addre_binary.length()-2-temp_size),temp_size);


}

string extract_index_bits1(string addre_binary)
{
	//cout<<temp_size<<endl;
	return addre_binary.substr((addre_binary.length()-2-size1),size1);


}

int bin2dec(string addre_binary)
{
	unsigned int value;
	//value=stoull(addre_binary,0,2);
	bitset<64> set(addre_binary);
	value=set.to_ulong();
	return value;
}

int gshare_stat(string linebuffer)
{

			
						string branch_status;
			string pc;
			int counter;
			string branch_index1;
			string branch_predict;
			int num_prediction=0;
			int branch_index;
			string tex1 ="tushar";

			string tex(1,tex1[0]);
			branch_status=linebuffer.substr((linebuffer.length()-1));
			temp_branch_status=linebuffer.substr((linebuffer.length()-1));
			pc=linebuffer.substr(0,(linebuffer.length()-2));
				
			//cout<<hex2bin(pc)<<endl;
			string pc_m=extract_index_bits((hex2bin(pc)),size1);
				//cout<<((pc_m))<<endl;

				branch_index1=((pc_m).substr(0,n1));
				
				n3=atoi(n2.c_str());
				
				//cout<<n3<<"   "<<(branch_index1.c_str())<<endl;
				int xor_output=(bin2dec(branch_index1.c_str()))^(bin2dec(n2.c_str()));
				//int xor_output=0;
				//cout<<xor_output<<endl;
				//cout<<"Executed"<<endl;
				

				
				string res;
				ostringstream convert;
				convert << xor_output;
				res=convert.str();
				res=bitset<64>(xor_output).to_string();

				string xor_binary_Final=res.substr(res.length()-n1,n1)+pc_m.substr(n1,pc_m.length()-n1);
				xor_binary_Final=xor_binary_Final.substr(xor_binary_Final.length()-size1,size1);
				//cout<<res.substr(res.length()-n1,n1)<<endl;
				//cout<<xor_binary_Final<<endl;
				branch_index=bin2dec(xor_binary_Final);
				//cout<<pc<<endl;
				//cout<<branch_index<<endl;
				gshare_index=branch_index;
				
				counter=gshare_table[branch_index];
				//cout<<gshare_index<<" "<<counter<<endl;
				if(counter>=2)
				{
					branch_predict='t';
					int ans=branch_predict.compare(branch_status);

				
					return 1;
				}	
				else
				{
					branch_predict='n';
					int ans=branch_predict.compare(branch_status);

				
					return 0;
				}

			
}

int bimodal_stat(string linebuffer)
{
			string branch_status;
			string pc;
			int counter;
			int branch_index;
			string branch_predict;
			branch_status=linebuffer.substr((linebuffer.length()-1));
			pc=linebuffer.substr(0,(linebuffer.length()-2));
			branch_index=bin2dec(extract_index_bits((hex2bin(pc)),m2));
			bimodal_index=branch_index;	
			

				counter=bimodal_table[branch_index];
				//cout<<bimodal_index<<" "<<counter<<endl;
			if(counter>=2)
				{
				branch_predict='t';
				int ans=branch_predict.compare(branch_status);

				
					return 1;
				}	
				else
				{
					branch_predict='n';
					int ans=branch_predict.compare(branch_status);

				
					return 0;
				}	

}

void update_table(int poroto,int outcome)
{
	string tex1 ="tushar";
	string tex(1,tex1[0]);
	string branch_status=temp_branch_status;
	string branch_predict1;
	if(outcome)
		 branch_predict1="t";
	else
		 branch_predict1="n";
	

	if (poroto)
	{
		int ans1=branch_status.compare(branch_predict1);
		if(ans1!=0)
				mispredict_counter++;

		int branch_index=gshare_index;
		int counter=gshare_table[gshare_index];
		if(counter>=2)
				{
					

				int ans1=branch_status.compare(tex);	
				if(ans1==0)
				{	
					if(counter<3)
					{
						gshare_table[branch_index]++;
						
					}
					else
						gshare_table[branch_index]=3;
				}
				else
				{
					if(counter>0)
						gshare_table[branch_index]--;
					else
						gshare_table[branch_index]=0;

				}
				}	
				else
				{
					
				
				int ans1=branch_status.compare(tex)	;

				if(ans1==0)
				{	
					if(counter<3)
					{
						gshare_table[branch_index]++;
						
					}
					else
						gshare_table[branch_index]=3;
				}
				else
				{
					if(counter>0)
						gshare_table[branch_index]--;
					else
						gshare_table[branch_index]=0;
					
				}
					
				}	
				//cout<<"execute"<<endl;
				//cout<<branch_index<<" "<<gshare_table[branch_index]<<endl;

	}
	else
	{
		int ans1=branch_status.compare(branch_predict1);
		if(ans1!=0)
				mispredict_counter++;

		int branch_index=bimodal_index;
		int counter=bimodal_table[bimodal_index];
				if(counter>=2)
				{
					
				int ans1=branch_status.compare(tex);	
				if(ans1==0)
				{	
					//cout<<ans1<<endl;
					if(counter<3)
					{
						bimodal_table[branch_index]++;
						
					}
					else
						bimodal_table[branch_index]=3;
				}
				else
				{
					//cout<<counter<<endl;
					if(counter>0)
						bimodal_table[branch_index]--;
					else
						bimodal_table[branch_index]=0;

				}
				}	
				else
				{
				
				
				int ans1=branch_status.compare(tex)	;

				if(ans1==0)
				{	
					if(counter<3)
					{
						bimodal_table[branch_index]++;
						
					}
					else
						bimodal_table[branch_index]=3;
				}
				else
				{
					if(counter>0)
						bimodal_table[branch_index]--;
					else
						bimodal_table[branch_index]=0;
					
				}
					
				}	
				
				
				//cout<<branch_index<<" "<<bimodal_table[branch_index]<<endl;

	}	



}

int main(int argc, char* argv[])
{
	
	string pro=argv[1];
	
		if(pro=="bimodal")
		{


			size1=atoi(argv[2]);
			size_table=pow(2,size1);
			vector<int> predict_table;
			predict_table.resize(size_table);
			//cout<<size_table<<endl;
			for(unsigned int i=0;i<size_table;i++) {
					predict_table[i]=2;
					}

			int mispredict_counter=0;
			int pre_input;
			ifstream trace_file(argv[3]);
			string linebuffer;
			string branch_status;
			string pc;
			int counter;
			int branch_index;
			string branch_predict;
			int num_prediction=0;
			string tex1 ="tushar";

			string tex(1,tex1[0]);
			while(trace_file && getline(trace_file, linebuffer))
			{
				if(linebuffer.length()==0) continue;
				branch_status=linebuffer.substr((linebuffer.length()-1));
				pc=linebuffer.substr(0,(linebuffer.length()-2));
				branch_index=bin2dec(extract_index_bits1(hex2bin(pc)));
				num_prediction++;
				counter=predict_table[branch_index];
				//cout<<counter<<endl;
				//cout<<branch_index<<endl;
				if(counter>=2)
				{
					branch_predict='t';

				int ans1=branch_status.compare(tex);	
				if(ans1==0)
				{	
					if(counter<3)
					{
						predict_table[branch_index]++;
						
					}
					else
						predict_table[branch_index]=3;
				}
				else
				{
					if(counter>0)
						predict_table[branch_index]--;
					else
						predict_table[branch_index]=0;

				}
				}	
				else
				{
					branch_predict='n';
				
				int ans1=branch_status.compare(tex)	;

				if(ans1==0)
				{	
					if(counter<3)
					{
						predict_table[branch_index]++;
						
					}
					else
						predict_table[branch_index]=3;
				}
				else
				{
					if(counter>0)
						predict_table[branch_index]--;
					else
						predict_table[branch_index]=0;
					
				}
					
				}	
				
				int ans=branch_predict.compare(branch_status);

				if(ans!=0)

				{
						//cout<<"Mispredicted"<<endl;
						mispredict_counter++;
				}
				//cout<<predict_table[branch_index]<<endl;		

			}	
			//cout<<pc<<endl;

	cout<<"COMMAND"<<endl;
	cout<<"./sim bimodal "<<argv[2]<<" "<<argv[3]<<endl<<"OUTPUT"<<endl;		
	cout<<"number of predictions: "<<num_prediction<<endl<<"number of mispredictions: "<<mispredict_counter<<endl;
	cout<<"misprediction rate: "<<setprecision(2)<<fixed<<(((float) mispredict_counter)/((float) num_prediction))*100<<"%"<<endl;
	cout<<"FINAL BIMODAL  CONTENTS"<<endl;
	for(unsigned int i=0;i<size_table;i++)
{
	cout<<i<<"  "<<predict_table[i]<<endl;

}
	}

	if(pro=="gshare")
	
	{

		size1=atoi(argv[2]);
			int n1=atoi(argv[3]);
			string n2;
			n2.append(n1,'0');
			//cout<<n2<<endl;
			int n3;
			n3=atol(n2.c_str());
			//cout<<n3<<endl;
			size_table=pow(2,size1);
			vector<int> predict_table;
			predict_table.resize(size_table);
			//cout<<size_table<<endl;
			for(unsigned int i=0;i<size_table;i++) {
					predict_table[i]=2;
					}

			int mispredict_counter=0;
			int pre_input;
			ifstream trace_file(argv[4]);
			string linebuffer;
			string branch_status;
			string pc;
			int counter;
			string branch_index1;
			string branch_predict;
			int num_prediction=0;
			int branch_index;
			string tex1 ="tushar";

			string tex(1,tex1[0]);
			while(trace_file && getline(trace_file, linebuffer))
			{
				
				if(linebuffer.length()==0) continue;
				branch_status=linebuffer.substr((linebuffer.length()-1));
				pc=linebuffer.substr(0,(linebuffer.length()-2));
				string pc_m=extract_index_bits1(hex2bin(pc));
				//cout<<((pc_m))<<endl;
				branch_index1=((pc_m).substr(0,n1));
				n3=atoi(n2.c_str());
				
				//cout<<n3<<"   "<<(branch_index1.c_str())<<endl;
				int xor_output=(bin2dec(branch_index1.c_str()))^(bin2dec(n2.c_str()));
				//int xor_output=0;
				//cout<<xor_output<<endl;
				//cout<<"Executed"<<endl;
				
				
				string res;
				ostringstream convert;
				convert << xor_output;
				res=convert.str();
				res=bitset<64>(xor_output).to_string();

				string xor_binary_Final=res.substr(res.length()-n1,n1)+pc_m.substr(n1,pc_m.length()-n1);
				
				//cout<<pc_m.substr(n1,pc_m.length()-n1)<<endl;
				//cout<<xor_binary_Final<<endl;
				branch_index=bin2dec(xor_binary_Final);
				//cout<<pc<<endl;
				//cout<<branch_index<<endl;
				num_prediction++;
				counter=predict_table[branch_index];
				//cout<<counter<<endl;
				//cout<<num_prediction<<endl;
				if(counter>=2)
				{
					branch_predict='t';

				int ans1=branch_status.compare(tex);	
				if(ans1==0)
				{	
					if(counter<3)
					{
						predict_table[branch_index]++;
						
					}
					else
						predict_table[branch_index]=3;
				}
				else
				{
					if(counter>0)
						predict_table[branch_index]--;
					else
						predict_table[branch_index]=0;

				}
				}	
				else
				{
					branch_predict='n';
				
				int ans1=branch_status.compare(tex)	;

				if(ans1==0)
				{	
					if(counter<3)
					{
						predict_table[branch_index]++;
						
					}
					else
						predict_table[branch_index]=3;
				}
				else
				{
					if(counter>0)
						predict_table[branch_index]--;
					else
						predict_table[branch_index]=0;
					
				}
					
				}	
				
				int ans=branch_predict.compare(branch_status);

				if(ans!=0)

				{
						//cout<<"Mispredicted"<<endl;
						mispredict_counter++;
				}
				//cout<<predict_table[branch_index]<<endl;

				//updating branch register
				
				//cout<<n2<<endl;
				int ans1=branch_status.compare(tex)	;
				if(ans1==0)
						n2="1"+n2.substr(0,n2.length()-1);
				else
						n2="0"+n2.substr(0,n2.length()-1);		

				//cout<<n2<<endl;
			}	
			//cout<<pc<<endl;

	cout<<"COMMAND"<<endl;
	cout<<"./sim gshare "<<argv[2]<<" "<<argv[3]<<" "<<argv[4]<<endl<<"OUTPUT"<<endl;		
	cout<<"number of predictions: "<<num_prediction<<endl<<"number of mispredictions: "<<mispredict_counter<<endl;
	cout<<"misprediction rate: "<<setprecision(2)<<fixed<<(((float) mispredict_counter)/((float) num_prediction))*100<<"%"<<endl;
	cout<<"FINAL GSHARE  CONTENTS"<<endl;
	for(unsigned int i=0;i<size_table;i++)
{
	cout<<i<<"  "<<predict_table[i]<<endl;

}

return 1;
	}





if(pro=="hybrid")
{





			k=atoi(argv[2]);
			m2=atoi(argv[5]);
			size1=atoi(argv[3]);
			n1=atoi(argv[4]);
			
			n2.append(n1,'0');
			//cout<<n2<<endl;
			
			n3=atol(n2.c_str());
			//cout<<n3<<endl;
			size_table=pow(2,k);
			vector<int> predict_table;
			predict_table.resize(pow(2,k));
			bimodal_table.resize(pow(2,m2));
			gshare_table.resize(pow(2,size1));
			//cout<<size_table<<endl;
			for(long int i=0;i<size_table;i++) {
					predict_table[i]=1;
					}

			for(long int i=0;i<pow(2,size1);i++) {
					gshare_table[i]=2;
										}		

			for(long int i=0;i<pow(2,m2);i++) {
					bimodal_table[i]=2;
					}
					

			int gshare;
			int bimodal;

			
			int pre_input;
			ifstream trace_file(argv[6]);
			string linebuffer;
			string branch_status;
			string pc;
			int counter;
			string branch_index1;
			string branch_predict;
			int num_prediction=0;
			int branch_index;

			string tex1 ="tushar";

			string tex(1,tex1[0]);
			while(trace_file && getline(trace_file, linebuffer))
			{
				
				if(linebuffer.length()==0) continue;
				
				
				gshare=gshare_stat(linebuffer);
				bimodal=bimodal_stat(linebuffer);

				//calculating predict table index

				branch_status=linebuffer.substr((linebuffer.length()-1));
				pc=linebuffer.substr(0,(linebuffer.length()-2));
				branch_index=bin2dec(extract_index_bits((hex2bin(pc)),k));
				num_prediction++;
				counter=predict_table[branch_index];
				//cout<<branch_index<<" "<<counter<<endl;
				if(counter>=2)
				{

					if(gshare)
						update_table(1,1);
					else
						update_table(1,0);

				}
				else
				{	
					if(bimodal)
						update_table(0,1);
					else
						update_table(0,0);
				}

				//cout<<"N2 ="<<n2<<endl;
				int ans1=branch_status.compare(tex);
				//update global n2 register
				if(ans1==0)
						n2="1"+n2.substr(0,n2.length()-1);
				else
						n2="0"+n2.substr(0,n2.length()-1);		
				//cout<<n2<<endl;

				
					
				//update chooser table
				int ans=branch_status.compare(tex);
				if(ans==0)
				{
					if(gshare==1 && bimodal==0) //gshare correct, bimodal incorrect
						{
							if(counter<3)
						{
						predict_table[branch_index]++;
						
						}
						else
						predict_table[branch_index]=3;
						}	
					if (gshare==0 && bimodal ==1) //gshare wrong, bimodal correxct	
						{

							if(counter>0)
						predict_table[branch_index]--;
							else
						predict_table[branch_index]=0;

						}
				}
				else
				{
					if(gshare==0 && bimodal==1) //gshare correct, bimodal incorrect
						{
							if(counter<3)
						{
						predict_table[branch_index]++;
						
						}
						else
						predict_table[branch_index]=3;
						}	
					if (gshare==1 && bimodal ==0) //gshare wrong, bimodal correxct	
						{

							if(counter>0)
						predict_table[branch_index]--;
							else
						predict_table[branch_index]=0;

						}

				}	

				

				//cout<<n2<<endl;
			}	
			//cout<<pc<<endl;

	cout<<"COMMAND"<<endl;
	cout<<"./sim hybrid "<<argv[2]<<" "<<argv[3]<<" "<<argv[4]<<" "<<argv[5]<<" "<<argv[6]<<endl<<"OUTPUT"<<endl;
	cout<<"number of predictions: "<<num_prediction<<endl<<"number of mispredictions: "<<mispredict_counter<<endl;
	cout<<"misprediction rate: "<<setprecision(2)<<fixed<<(((float) mispredict_counter)/((float) num_prediction))*100<<"%"<<endl;

cout<<"FINAL CHOOSER CONTENTS"<<endl;		
for(long int i=0;i<size_table;i++)
{
	cout<<i<<"  "<<predict_table[i]<<endl;

}
cout<<"FINAL GSHARE CONTENTS"<<endl;

for(long int i=0;i<pow(2,size1);i++)
{
	cout<<i<<" "<<gshare_table[i]<<endl;
}

cout<<"FINAL BIMODAL CONTENTS"<<endl;

for(long int i=0;i<pow(2,m2);i++)
{
	cout<<i<<" "<<bimodal_table[i]<<endl;
}

}

}