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

int size1; long long int size_table;
const int pc_size=6;

string hex2bin(string addre_hex)
{
	
	int addre_bin;
	istringstream st(addre_hex);
	st>>hex>>addre_bin;
	
	bitset<24> bits(addre_bin);
	
	string address_binary(bits.to_string());
	return address_binary;
	
}

string extract_index_bits(string addre_binary)
{
	//cout<<size<<endl;
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


int main(int argc, char* argv[])
{
	if(argc!=4)
	{
		cout<<"Incorrect arguments, Exiting"<<endl;
		return 0;
	}

	
			
			size1=atoi(argv[1]);
			int n1=atoi(argv[2]);
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
			ifstream trace_file(argv[3]);
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
				string pc_m=extract_index_bits(hex2bin(pc));
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
			cout<<num_prediction<<endl;
			cout<<mispredict_counter<<endl;
for(unsigned int i=0;i<size_table;i++)
{
	cout<<i<<"  "<<predict_table[i]<<endl;

}

}