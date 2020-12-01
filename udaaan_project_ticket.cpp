#include<bits/stdc++.h>

using namespace std;

class screen{
private:
    string name;
    int num_of_row;
    int seats_per_row;
    vector<int> aisle;
    vector<vector<bool> > seats;

public:
    screen(string screen_name,int row,int size,vector<int> list=vector<int> ()){
        name=screen_name;
        num_of_row=row;
        seats_per_row=size;
        aisle=list;
        seats = vector<vector<bool>> (row,vector<bool> (size,false));
    }
    void reserve_seat(int row,vector<int> list){
        if(row-1>num_of_row){
            cout<<"faliure"<<endl;
            return;
        }
        for(int i=0;i<list.size();i++){
            int inx=list[i]-1;
            if(seats[row][inx]==true){
                cout<<"faliure"<<endl;
                for(int j=i-1;j>=0;j--)
                    seats[row][j]=false;
                return;
            }
            seats[row][inx]=true;
        }
        cout<<"sucess"<<endl;
    }

    void get_unreserved_seats(int row){
        if(row-1>num_of_row){
            cout<<"faliure"<<endl;
            return;
        }
        for(int i=0;i<seats[row].size();i++){
            if(seats[row][i]==false)
                cout<<i+1<<" ";
        }
        cout<<endl;
    }
    void suggest_contigous_seats(int num,int row,int choice){
        if(row-1>num_of_row){
            cout<<"faliure"<<endl;
            return;
        }
        choice--;
        int l=choice-(num-1),h=choice+(num-1);
        bool can=false;
        for(int i=l;l>=0 && choice<seats[row].size() && i<=choice;i++){
            if(seats[row][i]==false && ((i==l || i==choice) || find(aisle.begin(),aisle.end(),i+1)==aisle.end())){
                can=true;
            }
            else{
                can=false;
                break;
            }
        }
        if(can==true){
            for(int i=l;i<=choice;i++)
                cout<<i+1<<" ";
            cout<<endl;
            return;
        }
        can=true;
        for(int i=choice;choice>=0 && h<seats[row].size() && i<=h;i++){
            if(seats[row][i]==false && ((i==h || i==choice) || find(aisle.begin(),aisle.end(),i+1)==aisle.end())){
                can=true;
            }
            else{
                can=false;
                break;
            }
        }
        if(can==true){
            for(int i=choice;i<=h;i++)
                cout<<i+1<<" ";
            cout<<endl;
            return;
        }
        cout<<"none"<<endl;
        return;
    }
};

class theatre{
private:
    vector<screen*> list_of_screen;
    map<string,int> map_of_screen;


    vector<int> get_numbers(){
        string s;
	    getline(cin,s);
	    vector<int> values;
	    int val=0;
	    int i=0,l=s.length();
	    while(i<l && s[i]==' ')
		    i++;
	    while(i<l){
		    if(s[i]==' '){
			    values.push_back(val);
			    val=0;
			    while(i<l && s[i]==' ')
				    i++;
			    continue;
		    }
		    val=10*val+s[i]-'0';
		    i++;
	    }
        if(val!=0)
            values.push_back(val);
	    return values;
    }

    void add_screen(string screen_name){
        if(map_of_screen[screen_name]!=0){
            cout<<"faliure"<<endl;
            return;
        }
        int row,size;
        cin>>row>>size;
        vector<int> list=get_numbers();
        //Checking validity of input
        for(int i=0;i<list.size();i++){
            if(list[i]>size){
                cout<<"faliure"<<endl;
                return;
            }
        }
        screen* new_screen = new screen(screen_name,row,size,list);
        list_of_screen.push_back(new_screen);
        map_of_screen[screen_name]=list_of_screen.size();
        cout<<"sucess"<<endl;
    }
    void reserve_seat(string screen_name){
        if(map_of_screen[screen_name]==0){
            cout<<"faliure"<<endl;
            return;
        }
        int row;
        cin>>row;
        vector<int> list=get_numbers();
        int inx=map_of_screen[screen_name]-1;
        list_of_screen[inx]->reserve_seat(row,list);
    }
    void get_unreserved_seats(string screen_name){
        if(map_of_screen[screen_name]==0){
            cout<<"faliure"<<endl;
            return;
        }
        int row;
        cin>>row;
        int inx=map_of_screen[screen_name]-1;
        list_of_screen[inx]->get_unreserved_seats(row);
    }

    void suggest(string screen_name){
        if(map_of_screen[screen_name]==0){
            cout<<"faliure"<<endl;
            return;
        }
        int num,row,choice;
        cin>>num>>row>>choice;
        int inx=map_of_screen[screen_name]-1;
        list_of_screen[inx]->suggest_contigous_seats(num,row,choice);
    }
public:
    void get_input(){
        string command,screen_name;
        cin>>command>>screen_name;
        if(command=="add-screen")
            add_screen(screen_name);
        else if(command=="reserve-seat")
            reserve_seat(screen_name);
        else if(command=="get-unreserved-seats")
            get_unreserved_seats(screen_name);
        else suggest(screen_name);
    }
};



int main(){
    int n;
    cin>>n;
    theatre th1;
    while(n--){
        th1.get_input();
    }
    return 0;
}

/*
Test Input:-
9
add-screen Screen1 12 10 4 5 8 9
add-screen Screen2 20 25 3 4 12 13 17 18
reserve-seat Screen1 4 5 6 7
reserve-seat Screen2 13 6 7 8 9 10
reserve-seat Screen2 13 4 5 6
get-unreserved-seats Screen2 13
suggest-contigous-seats Screen1 3 3 4
suggest-contigous-seats Screen2 4 12 4
suggest-contigous-seats Screen2 4 10 3
 
//end

Result:-
success
success
success
success
faliure
1 2 3 4 5 11 12 13 14 15 16 17 18 19 20 21 23 24 25
2 3 4
4 5 6 7
none
 
//end
*/