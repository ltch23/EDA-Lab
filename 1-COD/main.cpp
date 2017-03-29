#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>

#define LEN 1000
using namespace std;

vector<int> m_vector;

vector<vector<double>> gener(int len){
    ofstream numbers(to_string(len)+"d.txt");
    vector<vector<double>> m_rpta(LEN, vector<double>(len));
    srand(time(NULL));
    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < len; j++){
            m_rpta[i][j] = ((double)(rand() % 100 + 1) / 100);
            numbers<<to_string(m_rpta[i][j])+" ";
            //cout<<m_rpta[i][j]<<" ";
        }
        numbers<<"\n";
    }
    numbers.close();
    
    return m_rpta;
}

vector<double> mam(vector<vector<double>> m_data)
{
    vector<double> rpta(3);
    int len = m_data[0].size();
    double max = 0.0, aver = 0.0, tmp, min = 100.0;
    for (int i = 0; i < LEN; i++){
        for (int j = i + 1; j < LEN; j++){
            tmp = 0.0;
            for (int k = len - 1; k >= 0; k--)
                tmp += pow((m_data[i][k] - m_data[j][k]), 2);

            tmp = sqrt(tmp);
            if (tmp < min)
                min = tmp;
            else if (tmp > max)
                max = tmp;
            aver += tmp;
        }
    }
    aver = aver / (LEN * (LEN - 1) / 2);
    rpta[0] = min;
    rpta[1] = max;
    rpta[2] = aver;
    return rpta;
}

int main()
{
    unsigned int len;
    cout << "len: ";
    cin >> len;

    ofstream mime(to_string(len) + ".txt");
    vector<vector<double>> m_data = gener(len);
    vector<double> _mam = mam(m_data);

    return 0;
}
