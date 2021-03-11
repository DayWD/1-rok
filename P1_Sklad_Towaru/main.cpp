//Dawid Urbanik
#include <iostream>

using namespace std;

long long sum_up;

struct Place{       //  Miejsce na towar
    unsigned short amount_commodity;     // Ilosc towaru
    char label[2];

    void Vanish() {
        //    sum_up-=amount_commodity;
        amount_commodity = 0;
        label[0]='0';
        label[1]='0';
    }

};

struct Shelf{       //  Polka
    Place place[128];
    unsigned short amount_place;

    void SET_AP(int w,int r,int s,int p){
        for(int i=p;amount_place>i;i++){
            sum_up-=place[i].amount_commodity;
            place[i].Vanish();
        }
        for(int i=amount_place;p>i;i++){
            sum_up-=place[i].amount_commodity;
            place[i].Vanish();
        }
        amount_place = p;
    }

};

struct Rack{        //  Regal
    Shelf shelf[128];
    unsigned short amount_shelf;

    void SET_AS(int w,int r,int s,int p){
        for(int i=s;amount_shelf>i;i++){
            shelf[i].amount_place=0;
            for(int n=0;n<128;n++)
                sum_up-=shelf[i].place[n].amount_commodity;
        }
        for(int i=0;i<s;i++){
            shelf[i].SET_AP(w,r,s,p);
        }
        shelf[0].SET_AP(w,r,s,p);
        amount_shelf=s;
    }

};

struct Warehouse{       //  Magazyn
    Rack rack[128];
    unsigned short amount_rack;
    Shelf handyshelf;

    void SET_AR(int w,int r,int s,int p){
        for(int i=r;amount_rack>i;i++){
            rack[i].amount_shelf=0;
        }
        for(int i=0;i<r;i++){
            rack[i].SET_AS(w,r,s,p);
        }
        rack[0].SET_AS(w,r,s,p);
        amount_rack=r;
    }

};

struct Storehouse{       //  Sklad
    Warehouse warehouse[128];
    Rack handy_rack;
    Shelf handy_shelf;
    unsigned short amount_warehouse;
    unsigned short amount_handy_rack;

    void SET_AW(int w,int r,int s,int p){
        for(int i=w;amount_warehouse>i;i++){
            warehouse[i].amount_rack=0;
        }
        for(int i=0;i<w;i++){
            warehouse[i].SET_AR(w,r,s,p);
        }
        warehouse[0].SET_AR(w,r,s,p);
        amount_warehouse=w;
    }

}static storehouse;

void FILL(long long w,long long r,long long s,long long p,long long a){
    storehouse.handy_shelf.amount_place=p;
    storehouse.handy_rack.amount_shelf=s;
    //   cout<<sum_up<<endl;
    sum_up=0;
    sum_up+=a*w*r*s*p;
    sum_up+=a*w*p;
    sum_up+=a*p;
    sum_up+=a*s*p;
    for(int i=0;i<w;i++){
        for(int k=0;k<r;k++){
            for(int l=0;l<s;l++){
                for(int m=0;m<p;m++){
                    storehouse.warehouse[i].rack[k].shelf[l].place[m].Vanish();
                    storehouse.warehouse[i].rack[k].shelf[l].place[m].amount_commodity=a;

                    storehouse.warehouse[i].handyshelf.place[m].Vanish();
                    storehouse.warehouse[i].handyshelf.place[m].amount_commodity=a;

                    storehouse.handy_shelf.place[m].Vanish();
                    storehouse.handy_shelf.place[m].amount_commodity=a;

                    storehouse.handy_rack.shelf[l].place[m].Vanish();
                    storehouse.handy_rack.shelf[l].place[m].amount_commodity=a;
                }
                storehouse.warehouse[i].rack[k].shelf[l].amount_place=p;
                storehouse.warehouse[i].handyshelf.amount_place=p;
                storehouse.handy_rack.shelf[l].amount_place=p;
            }
            storehouse.warehouse[i].rack[k].amount_shelf=s;
        }
        storehouse.warehouse[i].amount_rack=r;
    }
    storehouse.amount_warehouse=w;
}

void GET_W(int w){
    long long ilosc=0;
    for(int k=0;k<storehouse.warehouse[w].amount_rack;k++){
        for(int m=0;m<storehouse.warehouse[w].rack[k].amount_shelf;m++){
            for(int n=0;n<storehouse.warehouse[w].rack[k].shelf[m].amount_place;n++){
                ilosc+=storehouse.warehouse[w].rack[k].shelf[m].place[n].amount_commodity;
            }
        }
    }
    for(int n=0;n<storehouse.warehouse[w].handyshelf.amount_place;n++){
        ilosc+=storehouse.warehouse[w].handyshelf.place[n].amount_commodity;
    }
    cout<<ilosc<<endl;
}
void GET_RW(int w,int r){
    long long ilosc=0;
    for(int m=0;m<storehouse.warehouse[w].rack[r].amount_shelf;m++){
        for(int n=0;n<storehouse.warehouse[w].rack[r].shelf[m].amount_place;n++){
            ilosc+=storehouse.warehouse[w].rack[r].shelf[m].place[n].amount_commodity;
        }
    }
    cout<<ilosc<<endl;
}
void GET_RH(){
    long long ilosc=0;
    for(int m=0;m<storehouse.handy_rack.amount_shelf;m++){
        for(int n=0;n<storehouse.handy_rack.shelf[m].amount_place;n++){
            ilosc+=storehouse.handy_rack.shelf[m].place[n].amount_commodity;
        }
    }
    cout<<ilosc<<endl;
}
void GET_SW(int w,int r,int s){
    long long ilosc=0;
    for(int n=0;n<storehouse.warehouse[w].rack[r].shelf[s].amount_place;n++){
        ilosc+=storehouse.warehouse[w].rack[r].shelf[s].place[n].amount_commodity;
    }
    cout<<ilosc<<endl;
}
void GET_SH(int w){
    long long ilosc=0;
    for(int n=0;n<storehouse.warehouse[w].handyshelf.amount_place;n++){
        ilosc+=storehouse.warehouse[w].handyshelf.place[n].amount_commodity;
    }
    cout<<ilosc<<endl;
}
void GET_SR(int s){
    long long ilosc=0;
    for(int n=0;n<storehouse.handy_rack.shelf[s].amount_place;n++){
        ilosc+=storehouse.handy_rack.shelf[s].place[n].amount_commodity;
    }
    cout<<ilosc<<endl;
}
void GET_S(){
    long long ilosc=0;
    for(int n=0;n<storehouse.handy_shelf.amount_place;n++){
        ilosc+=storehouse.handy_shelf.place[n].amount_commodity;
    }
    cout<<ilosc<<endl;
}
//Polecenia Etykietowe
void SET_LW(int w,int r,int s,int p,char etykieta1,char etykieta2){
    storehouse.warehouse[w].rack[r].shelf[s].place[p].label[0]=etykieta1;
    storehouse.warehouse[w].rack[r].shelf[s].place[p].label[1]=etykieta2;
}
void SET_LH(int w,int p,char etykieta1,char etykieta2){
    storehouse.warehouse[w].handyshelf.place[p].label[0]=etykieta1;
    storehouse.warehouse[w].handyshelf.place[p].label[1]=etykieta2;
}
void SET_LR(int s,int p,char etykieta1,char etykieta2){
    storehouse.handy_rack.shelf[s].place[p].label[0]=etykieta1;
    storehouse.handy_rack.shelf[s].place[p].label[1]=etykieta2;
}
void SET_LS(int p,char etykieta1,char etykieta2){
    storehouse.handy_shelf.place[p].label[0]=etykieta1;
    storehouse.handy_shelf.place[p].label[1]=etykieta2;
}
void GET_LW(int w,int r,int s,int p){
    cout<<storehouse.warehouse[w].rack[r].shelf[s].place[p].label[0];
    cout<<storehouse.warehouse[w].rack[r].shelf[s].place[p].label[1]<<endl;
}
void GET_LH(int w,int p){
    cout<<storehouse.warehouse[w].handyshelf.place[p].label[0];
    cout<<storehouse.warehouse[w].handyshelf.place[p].label[1]<<endl;
}
void GET_LR(int s,int p){
    cout<<storehouse.handy_rack.shelf[s].place[p].label[0];
    cout<<storehouse.handy_rack.shelf[s].place[p].label[1]<<endl;
}
void GET_LS(int p){
    cout<<storehouse.handy_shelf.place[p].label[0];
    cout<<storehouse.handy_shelf.place[p].label[1]<<endl;
}

void PUT_W(int w,int r,int s,int p,int a){
    if(w>=storehouse.amount_warehouse||r>=storehouse.warehouse[w].amount_rack||s>=storehouse.warehouse[w].rack[r].amount_shelf||p>=storehouse.warehouse[w].rack[r].shelf[s].amount_place)
        cout<<"error"<<endl;
    else{
        if(storehouse.warehouse[w].rack[r].shelf[s].place[p].amount_commodity+a>65535){
            sum_up+=65535-storehouse.warehouse[w].rack[r].shelf[s].place[p].amount_commodity;
            storehouse.warehouse[w].rack[r].shelf[s].place[p].amount_commodity=65535;
        }
        else{
            storehouse.warehouse[w].rack[r].shelf[s].place[p].amount_commodity+=a;
            sum_up+=a;
        }
    }
}
void PUT_H(int w,int p,int a){
    if(w>=storehouse.amount_warehouse||p>=storehouse.warehouse[w].handyshelf.amount_place)
        cout<<"error"<<endl;
    else{
        if(storehouse.warehouse[w].handyshelf.place[p].amount_commodity+a>65535){
            sum_up+=65535-storehouse.warehouse[w].handyshelf.place[p].amount_commodity;
            storehouse.warehouse[w].handyshelf.place[p].amount_commodity=65535;
        }
        else{
            storehouse.warehouse[w].handyshelf.place[p].amount_commodity+=a;
            sum_up+=a;
        }
    }
}
void PUT_R(int s,int p,int a){
    if(s>=storehouse.handy_rack.amount_shelf||p>=storehouse.handy_rack.shelf[s].amount_place)
        cout<<"error"<<endl;
    else{
        if(storehouse.handy_rack.shelf[s].place[p].amount_commodity+a>65535){
            sum_up+=65535-storehouse.handy_rack.shelf[s].place[p].amount_commodity;
            storehouse.handy_rack.shelf[s].place[p].amount_commodity=65535;
        }
        else{
            storehouse.handy_rack.shelf[s].place[p].amount_commodity+=a;
            sum_up+=a;
        }
    }
}
void PUT_S(int p,int a){
    if(p>=storehouse.handy_shelf.amount_place)
        cout<<"error"<<endl;
    else{
        if(storehouse.handy_shelf.place[p].amount_commodity+a>65535){
            sum_up+=65535-storehouse.handy_shelf.place[p].amount_commodity;
            storehouse.handy_shelf.place[p].amount_commodity=65535;
        }
        else{
            storehouse.handy_shelf.place[p].amount_commodity+=a;
            sum_up+=a;
        }
    }
}

void POP_W(int w,int r,int s,int p,int a){
    if(w>=storehouse.amount_warehouse||r>=storehouse.warehouse[w].amount_rack||s>=storehouse.warehouse[w].rack[r].amount_shelf||p>=storehouse.warehouse[w].rack[r].shelf[s].amount_place)
        cout<<"error"<<endl;
    else{
        if(storehouse.warehouse[w].rack[r].shelf[s].place[p].amount_commodity-a<0){
            sum_up-=storehouse.warehouse[w].rack[r].shelf[s].place[p].amount_commodity;
            storehouse.warehouse[w].rack[r].shelf[s].place[p].amount_commodity=0;
        }
        else{
            storehouse.warehouse[w].rack[r].shelf[s].place[p].amount_commodity-=a;
            sum_up-=a;
        }
    }
}
void POP_H(int w,int p,int a){
    if(w>=storehouse.amount_warehouse||p>=storehouse.warehouse[w].handyshelf.amount_place)
        cout<<"error"<<endl;
    else{
        if(storehouse.warehouse[w].handyshelf.place[p].amount_commodity-a<0){
            sum_up-=storehouse.warehouse[w].handyshelf.place[p].amount_commodity;
            storehouse.warehouse[w].handyshelf.place[p].amount_commodity=0;
        }
        else{
            storehouse.warehouse[w].handyshelf.place[p].amount_commodity-=a;
            sum_up-=a;
        }
    }
}
void POP_R(int s,int p,int a){
    if(s>=storehouse.handy_rack.amount_shelf||p>=storehouse.handy_rack.shelf[s].amount_place)
        cout<<"error"<<endl;
    else{
        if(storehouse.handy_rack.shelf[s].place[p].amount_commodity-a<0){
            sum_up-=storehouse.handy_rack.shelf[s].place[p].amount_commodity;
            storehouse.handy_rack.shelf[s].place[p].amount_commodity=0;
        }
        else{
            storehouse.handy_rack.shelf[s].place[p].amount_commodity-=a;
            sum_up-=a;
        }
    }
}
void POP_S(int p,int a){
    if(p>=storehouse.handy_shelf.amount_place)
        cout<<"error"<<endl;
    else{
        if(storehouse.handy_shelf.place[p].amount_commodity-a<0){
            sum_up-=storehouse.handy_shelf.place[p].amount_commodity;
            storehouse.handy_shelf.place[p].amount_commodity=0;
        }
        else{
            storehouse.handy_shelf.place[p].amount_commodity-=a;
            sum_up-=a;
        }
    }
}

int main()
{
    int w,r,s,p,a,w2,r2,s2;
    char etykieta1,etykieta2;
    string symbol;
    while(2==2){
        cin>>symbol;
        if(symbol=="SET-AP"){
            cin>>w>>r>>s>>p;
            if(w>=storehouse.amount_warehouse||r>=storehouse.warehouse[w].amount_rack||s>=storehouse.warehouse[w].rack[r].amount_shelf||p>128)
                cout<<"error"<<endl;
            else
                storehouse.warehouse[w].rack[r].shelf[s].SET_AP(w,r,s,p);
        }
        else if(symbol=="TEST"){
            cin>>w>>r>>s>>p;
            cout<<storehouse.amount_warehouse<<endl;
            cout<<storehouse.warehouse[w].amount_rack<<endl;
            cout<<storehouse.warehouse[w].rack[r].amount_shelf<<endl;
            cout<<storehouse.warehouse[w].rack[r].shelf[s].amount_place<<endl;
            cout<<storehouse.warehouse[w].rack[r].shelf[s].place[p].amount_commodity<<endl;
            cout<<"podreczna_polka = "<<storehouse.warehouse[w].handyshelf.amount_place<<endl;
            cout<<"ilosc towaru = "<<storehouse.warehouse[w].handyshelf.place[p].amount_commodity<<endl;
            cout<<"sum_up = "<<sum_up<<endl;
        }
        else if(symbol=="SET-AS"){
            cin>>w>>r>>s>>p;
            if(w>=storehouse.amount_warehouse||r>=storehouse.warehouse[w].amount_rack||s>128||p>128)
                cout<<"error"<<endl;
            else
                storehouse.warehouse[w].rack[r].SET_AS(w,r,s,p);
        }
        else if(symbol=="SET-AR"){
            cin>>w>>r>>s>>p;
            if(w>=storehouse.amount_warehouse||r>128||s>128||p>128)
                cout<<"error"<<endl;
            else
                storehouse.warehouse[w].SET_AR(w,r,s,p);
        }
        else if(symbol=="SET-AW"){
            cin>>w>>r>>s>>p;
            if(w>128||r>128||s>128||p>128)
                cout<<"error"<<endl;
            else
                storehouse.SET_AW(w,r,s,p);
        }
        else if(symbol=="SET-HW"){
            cin>>w>>p;
            if(w>=storehouse.amount_warehouse||p>128)
                cout<<"error"<<endl;
            else
                storehouse.warehouse[w].handyshelf.SET_AP(w,0,0,p);
        }
        else if(symbol=="SET-HR"){
            cin>>s>>p;
            if(s>128||p>128)
                cout<<"error"<<endl;
            else
                storehouse.handy_rack.SET_AS(0,0,s,p);
        }
        else if(symbol=="SET-HS"){
            cin>>p;
            if(p>128)
                cout<<"error"<<endl;
            else
                storehouse.handy_shelf.SET_AP(0,0,0,p);
        }
            //Polecenie dodajÄce towary
        else if(symbol=="PUT-W"){
            cin>>w>>r>>s>>p>>a;
            PUT_W(w,r,s,p,a);
        }
        else if(symbol=="PUT-H"){
            cin>>w>>p>>a;
            PUT_H(w,p,a);
        }
        else if(symbol=="PUT-R"){
            cin>>s>>p>>a;
            PUT_R(s,p,a);
        }
        else if(symbol=="PUT-S"){
            cin>>p>>a;
            PUT_S(p,a);
        }
            //Polecenie jednoczesnie nadajace strukture oraz ilosc towaru
        else if(symbol=="FILL"){
            cin>>w>>r>>s>>p>>a;
            if(w>128||r>128||s>128||p>128)
                cout<<"error"<<endl;
            else{
                FILL(w,r,s,p,a);
            }
        }
            //Polecenie odejmujace towar
        else if(symbol=="POP-W"){
            cin>>w>>r>>s>>p>>a;
            POP_W(w,r,s,p,a);
        }
        else if(symbol=="POP-H"){
            cin>>w>>p>>a;
            POP_H(w,p,a);
        }
        else if(symbol=="POP-R"){
            cin>>s>>p>>a;
            POP_R(s,p,a);
        }
        else if(symbol=="POP-S"){
            cin>>p>>a;
            POP_S(p,a);
        }
            //Polecenie przenoszace towar
        else if(symbol=="MOV-W"){
            unsigned short ilosc=0;
            cin>>w>>r>>s>>w2>>r2>>s2>>p>>a;
            if(w>=storehouse.amount_warehouse||r>=storehouse.warehouse[w].amount_rack||s>=storehouse.warehouse[w].rack[r].amount_shelf||p>=storehouse.warehouse[w].rack[r].shelf[s].amount_place||w2>=storehouse.amount_warehouse||r2>=storehouse.warehouse[w].amount_rack||s2>=storehouse.warehouse[w].rack[r].amount_shelf)
                cout<<"error"<<endl;
            else{
                for(int i=0;i<a;i++){
                    if(storehouse.warehouse[w].rack[r].shelf[s].place[p].amount_commodity-1<0||storehouse.warehouse[w2].rack[r2].shelf[s2].place[p].amount_commodity+1>65535)
                        break;
                    else{
                        storehouse.warehouse[w].rack[r].shelf[s].place[p].amount_commodity-=1;
                        storehouse.warehouse[w2].rack[r2].shelf[s2].place[p].amount_commodity+=1;
                        ilosc++;
                    }
                }
            }
        }
        else if(symbol=="MOV-H"){
            unsigned short ilosc=0;
            cin>>w>>r>>s>>p>>a;
            if(w>=storehouse.amount_warehouse||r>=storehouse.warehouse[w].amount_rack||s>=storehouse.warehouse[w].rack[r].amount_shelf||p>=storehouse.warehouse[w].rack[r].shelf[s].amount_place||p>=storehouse.warehouse[w].handyshelf.amount_place)
                cout<<"error"<<endl;
            else{
                for(int i=0;i<a;i++){
                    if(storehouse.warehouse[w].rack[r].shelf[s].place[p].amount_commodity-1<0||storehouse.warehouse[w].handyshelf.place[p].amount_commodity+1>65535)
                        break;
                    else{
                        storehouse.warehouse[w].rack[r].shelf[s].place[p].amount_commodity-=1;
                        storehouse.warehouse[w].handyshelf.place[p].amount_commodity+=1;
                        ilosc++;
                    }
                }
            }
        }
        else if(symbol=="MOV-R"){
            unsigned short ilosc=0;
            cin>>w>>r>>s>>s2>>p>>a;
            if(w>=storehouse.amount_warehouse||r>=storehouse.warehouse[w].amount_rack||s>=storehouse.warehouse[w].rack[r].amount_shelf||p>=storehouse.warehouse[w].rack[r].shelf[s].amount_place||s2>=storehouse.handy_rack.amount_shelf||p>=storehouse.handy_rack.shelf[s2].amount_place)
                cout<<"error"<<endl;
            else{
                for(int i=0;i<a;i++){
                    if(storehouse.warehouse[w].rack[r].shelf[s].place[p].amount_commodity-1<0||storehouse.handy_rack.shelf[s2].place[p].amount_commodity+1>65535)
                        break;
                    else{
                        storehouse.warehouse[w].rack[r].shelf[s].place[p].amount_commodity-=1;
                        storehouse.handy_rack.shelf[s2].place[p].amount_commodity+=1;
                        ilosc++;
                    }
                }
            }
        }
        else if(symbol=="MOV-S"){
            unsigned short ilosc=0;
            cin>>s>>p>>a;
            if(s>=storehouse.handy_rack.amount_shelf||p>=storehouse.handy_rack.shelf[s].amount_place||p>=storehouse.handy_shelf.amount_place)
                cout<<"error"<<endl;
            else{
                for(int i=0;i<a;i++){
                    if(storehouse.handy_rack.shelf[s].place[p].amount_commodity-1<0||storehouse.handy_shelf.place[p].amount_commodity+1>65535)
                        break;
                    else{
                        storehouse.handy_rack.shelf[s].place[p].amount_commodity-=1;
                        storehouse.handy_shelf.place[p].amount_commodity+=1;
                        ilosc++;
                    }
                }
            }
        }
            //Polecenie wyswietlajace informacje

        else if(symbol=="GET-E"){
            //         GET_E();
            cout<<sum_up<<endl;
        }
        else if(symbol=="GET-W"){
            cin>>w;
            if(w>=storehouse.amount_warehouse)
                cout<<"error"<<endl;
            else
                GET_W(w);
        }
        else if(symbol=="GET-RW"){
            cin>>w>>r;
            if(w>=storehouse.amount_warehouse||r>=storehouse.warehouse[w].amount_rack)
                cout<<"error"<<endl;
            else
                GET_RW(w,r);
        }       // ````````````````````````````````````````````````````````````````````````````
        else if(symbol=="GET-RH"){
            GET_RH();
        }
        else if(symbol=="GET-SW"){
            cin>>w>>r>>s;
            if(w>=storehouse.amount_warehouse||r>=storehouse.warehouse[w].amount_rack||s>=storehouse.warehouse[w].rack[r].amount_shelf)
                cout<<"error"<<endl;
            else
                GET_SW(w,r,s);
        }
        else if(symbol=="GET-SH"){
            cin>>w;
            if(w>=storehouse.amount_warehouse)
                cout<<"error"<<endl;
            else
                GET_SH(w);
        }
        else if(symbol=="GET-SR"){
            cin>>s;
            if(s>=storehouse.handy_rack.amount_shelf)
                cout<<"error"<<endl;
            else
                GET_SR(s);
        }
        else if(symbol=="GET-S"){
            GET_S();
        }
            //Polecenia etykietowe
        else if(symbol=="SET-LW"){
            cin>>w>>r>>s>>p>>etykieta1>>etykieta2;
            if(w>=storehouse.amount_warehouse||r>=storehouse.warehouse[w].amount_rack||s>=storehouse.warehouse[w].rack[r].amount_shelf||p>=storehouse.warehouse[w].rack[r].shelf[s].amount_place)
                cout<<"error"<<endl;
            else
                SET_LW(w,r,s,p,etykieta1,etykieta2);
        }
        else if(symbol=="SET-LH"){
            cin>>w>>p>>etykieta1>>etykieta2;
            if(w>=storehouse.amount_warehouse||p>=storehouse.handy_shelf.amount_place)
                cout<<"error"<<endl;
            else
                SET_LH(w,p,etykieta1,etykieta2);
        }
        else if(symbol=="SET-LR"){
            cin>>s>>p>>etykieta1>>etykieta2;
            if(s>=storehouse.handy_rack.amount_shelf||p>=storehouse.handy_rack.shelf[s].amount_place)
                cout<<"error"<<endl;
            else
                SET_LR(s,p,etykieta1,etykieta2);
        }
        else if(symbol=="SET-LS"){
            cin>>p>>etykieta1>>etykieta2;
            if(p>=storehouse.handy_shelf.amount_place)
                cout<<"error"<<endl;
            else
                SET_LS(p,etykieta1,etykieta2);
        }
        else if(symbol=="GET-LW"){
            cin>>w>>r>>s>>p;
            if(w>=storehouse.amount_warehouse||r>=storehouse.warehouse[w].amount_rack||s>=storehouse.warehouse[w].rack[r].amount_shelf||p>=storehouse.warehouse[w].rack[r].shelf[s].amount_place)
                cout<<"error"<<endl;
            else{
                if(storehouse.warehouse[w].rack[r].shelf[s].place[p].label[0]=='0'&&storehouse.warehouse[w].rack[r].shelf[s].place[p].label[1]=='0')
                    cout<<"--"<<endl;
                else
                    GET_LW(w,r,s,p);
            }
        }
        else if(symbol=="GET-LH"){
            cin>>w>>p;
            if(w>=storehouse.amount_warehouse||p>=storehouse.handy_shelf.amount_place)
                cout<<"error"<<endl;
            else{
                if(storehouse.warehouse[w].handyshelf.place[p].label[0]=='0'&&storehouse.warehouse[w].handyshelf.place[p].label[1]=='0')
                    cout<<"--"<<endl;
                else
                    GET_LH(w,p);
            }
        }
        else if(symbol=="GET-LR"){
            cin>>s>>p;
            if(s>=storehouse.handy_rack.amount_shelf||p>=storehouse.handy_rack.shelf[s].amount_place)
                cout<<"error"<<endl;
            else{
                if(storehouse.handy_rack.shelf[s].place[p].label[0]=='0'&&storehouse.handy_rack.shelf[s].place[p].label[1]=='0')
                    cout<<"--"<<endl;
                else
                    GET_LR(s,p);
            }
        }
        else if(symbol=="GET-LS"){
            cin>>p;
            if(p>=storehouse.handy_shelf.amount_place)
                cout<<"error"<<endl;
            else{
                if(storehouse.handy_shelf.place[p].label[0]=='0'&&storehouse.handy_shelf.place[p].label[1]=='0')
                    cout<<"--"<<endl;
                else
                    GET_LS(p);
            }
        }
        else if(symbol=="END"){
            break;
        }
    }
}
