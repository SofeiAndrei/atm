#include <iostream>
using namespace std;
class ATM{
    private:
        int hundr_5;
        int hundr_2;
        int hundr_1;
        int ten_5;
        int ten_2;
        int ten_1;
        int fives;
        bool has_card_inserted=0;
    public:
        ATM(){
            this->hundr_5 = 10;
            this->hundr_2 = 10;
            this->hundr_1 = 10;
            this->ten_5 = 10;
            this->ten_2 = 10;
            this->ten_1 = 10;
            this->fives = 10;
            this->has_card_inserted = 0;
        }
        void fill_atm(){
            this->hundr_5 = 10;
            this->hundr_2 = 10;
            this->hundr_1 = 10;
            this->ten_5 = 10;
            this->ten_2 = 10;
            this->ten_1 = 10;
            this->fives = 10;
            this->has_card_inserted = 0;
        }
        bool get_has_card_inserted(){
            return this->has_card_inserted;
        }
        void set_has_card_inserted(bool has_card_inserted){
            this->has_card_inserted = has_card_inserted;
        }
        void set_bills(int bills[7]){
            this->hundr_5 -= bills[0];
            this->hundr_2 -= bills[1];
            this->hundr_1 -= bills[2];
            this->ten_5 -= bills[3];
            this->ten_2 -= bills[4];
            this->ten_1 -= bills[5];
            this->fives -= bills[6];
        }
        void show_bills(){
            cout<<"500s: "<<this->hundr_5<<'\n';
            cout<<"200s: "<<this->hundr_2<<'\n';
            cout<<"100s: "<<this->hundr_1<<'\n';
            cout<<"50s: "<<this->ten_5<<'\n';
            cout<<"20s: "<<this->ten_2<<'\n';
            cout<<"10s: "<<this->ten_1<<'\n';
            cout<<"5s: "<<this->fives<<'\n';
        }
        bool can_provide(int amount){
            int left_amount = amount;
            int used_bills[7];
            for(int i=0;i<7;i++){
                if(i==0){
                    used_bills[i]=left_amount/500;
                    if(this->hundr_5 < used_bills[i]){
                        left_amount -= this->hundr_5*500;
                    }
                    else
                    left_amount -= (left_amount/500)*500;
                }
                else
                if(i==1){
                    used_bills[i]=left_amount/200;
                    if(this->hundr_2 < used_bills[i]){
                        left_amount -= this->hundr_2*200;
                    }
                    else
                    left_amount -= (left_amount/200)*200;
                }
                else
                if(i==2){
                    used_bills[i]=left_amount/100;
                    if(this->hundr_1 < used_bills[i]){
                        left_amount -= this->hundr_1*100;
                    }
                    else
                    left_amount -= (left_amount/100)*100;
                }
                else
                if(i==3){
                    used_bills[i]=left_amount/50;
                    if(this->ten_5 < used_bills[i]){
                        left_amount -= this->ten_5*50;
                    }
                    else
                    left_amount -= (left_amount/50)*50;
                }
                else
                if(i==4){
                    used_bills[i]=left_amount/20;
                    if(this->ten_2 < used_bills[i]){
                        left_amount -= this->ten_2*20;
                    }
                    else
                    left_amount -= (left_amount/20)*20;
                }
                else
                if(i==5){
                    used_bills[i]=left_amount/10;
                    if(this->ten_1 < used_bills[i]){
                        left_amount -= this->ten_1*10;
                    }
                    else
                    left_amount -= (left_amount/10)*10;
                }
                else{
                    used_bills[i]=left_amount/5;
                    if(this->fives < used_bills[i]){
                        left_amount -= this->fives*5;
                    }
                    else
                    left_amount -= (left_amount/5)*5;
                }
            }
            if(left_amount > 0 ){
                cout<<"The machine does not have enough funds, please enter a smaller amount\n";
                return 0;
            }
            else{
                this->set_bills(used_bills);
                return 1;
            }
        }
};
class credit_card{
    private:
        int balance;
    public:
        credit_card(){
            this->balance = 0;
        }
        credit_card(bool is_gold_card){
            if(is_gold_card == 1){
                this->balance = 1000;
            }
            else{
                this->balance = 500;
            }
        }
        bool validate_credentials(){
            long long number;
            int pin;
            cout<<"Enter the card number:\n";
            cin>>number;
            cout<<"Enter the pin:\n";
            cin>>pin;
            if(pin!=1234){
                return 0;
            }
            return 1;
        }
        int get_balance(){
            return this->balance;
        }
        void set_balance(int balance){
            this->balance = balance;
        }
        credit_card& operator=(const credit_card& card){
            if(this != &card){
                this->balance=card.balance;
            }
            return *this;
        }
};
class user{
    private:
        credit_card user_card;
    public:
        user(bool has_gold_card){
            credit_card temp_card(has_gold_card);
            this->user_card = temp_card;
        }
        credit_card get_card(){
            return this->user_card;
        }
        void update_card_balance(int balance){
            this->user_card.set_balance(balance);
        }
};
int main()
{
    while(true){
        ATM atm;
        cout<<"Available commands:\n";
        cout<<"If you want to go to the next day press 0\n";
        cout<<"If you want to do something else press 1\n";
        cout<<"If you want to stop the program press 2\n";
        int command;
        cin>>command;
        switch(command){
            case 0:{
                atm.show_bills();
                atm.fill_atm();
                break;
            }
            case 1:{
                bool is_gold_user;
                cout<<"If the current user is a gold user press 1, otherwise press 0\n";
                cin>>is_gold_user;
                user current_user(is_gold_user);
                bool OK=1;
                while(OK==1){
                    if(atm.get_has_card_inserted()==0){
                        cout<<"Enter the card with credentials:\n";
                        if(current_user.get_card().validate_credentials()==0){
                            cout<<"The pin introduced is not correct!\n";
                        }
                        else
                        atm.set_has_card_inserted(1);
                    }
                    else{
                        cout<<"If you want to make another operation press 1\n";
                        cout<<"If you want to eject the card press 0\n";
                        int user_command;
                        cin>>user_command;
                        switch(user_command){
                            case 0:{
                                OK=0;
                                break;
                            }
                            case 1:{
                                cout<<"If you want to display the balance press 1\n";
                                cout<<"If you want to make a withdrawal press 2\n";
                                int user_operation;
                                cin>>user_operation;
                                switch(user_operation){
                                    case 1:{
                                        cout<<current_user.get_card().get_balance()<<'\n';
                                        break;
                                    }
                                    case 2:{
                                        cout<<"Enter the amount\n";
                                        int amount=1;
                                        while(amount%10!=0){
                                            cout<<"The amount must be a multiple of 10!\n";
                                            cin>>amount;
                                        }
                                        if(amount > current_user.get_card().get_balance()){
                                            cout<<"Insufficient Funds\n";
                                        }
                                        else{
                                            if(atm.can_provide(amount)==1){
                                                int new_balance = current_user.get_card().get_balance() - amount;
                                                current_user.update_card_balance(new_balance);
                                            }
                                            atm.show_bills();
                                        }
                                        break;
                                    }
                                    default:{
                                        cout<<"Unknown command\n";
                                        break;
                                    }
                                }
                                break;
                            }
                            default:{
                                cout<<"Unknown command\n";
                                break;
                            }
                        }
                    }
                }
                atm.set_has_card_inserted(0);
                break;
            }
            case 2:{
                return 0;
            }
            default:{
                cout<<"Unknown command\n";
                break;
            }
        }
    }
}
