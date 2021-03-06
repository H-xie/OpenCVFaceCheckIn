#include "welcome.h"
#include "cameraget.h"
#include "authentication.h"
//#include "alert.h"
#include "admincheck.h"
#include "administor.h"
#include "sqlitetool.h"
#include "showfaces.h"

#include <QApplication>

int main(int argc, char *argv[])
{     

    // Create "../data/" folder
    QDir dirDatabase;
    if(!dirDatabase.exists("../data/")){
        dirDatabase.mkdir("../data/");
        cout << "makepath" << endl;
    }
    QApplication a(argc, argv);

    SQLiteTool sq;
    if(sq.initial())
        std::cout << "Initialization done."<< endl;

    //    ShowFaces s;
    //    s.start(1,"");


    Welcome w;
    CameraGet c;
    Authentication au;
//    Alert al;
    AdminCheck ac;
    Administor ad;
    ShowFaces s;

    w.setWindowFlags(Qt::FramelessWindowHint);
    //    c.setWindowFlags(Qt::FramelessWindowHint);
    au.setWindowFlags(Qt::FramelessWindowHint);

    w.show();

//    // Alert back to welcome all the time
//    QObject::connect(&al, SIGNAL(back(int)), &w, SLOT(reShow(int)));

    // Connect welcome and cameraget
    QObject::connect(&w, SIGNAL(confirmed(int, QString)), &c, SLOT(start(int, QString)));
    QObject::connect(&c, SIGNAL(back(int)), &w, SLOT(reShow(int)));

    // Connect cameraget and authentication
    QObject::connect(&c, SIGNAL(confirmed(int, QString)), &au, SLOT(start(int, QString)));
    //    QObject::connect(&a, SIGNAL())

//    // Connect everything and alert
//    QObject::connect(&c, SIGNAL(noFace(int,int,QString)), &al, SLOT(start(int,int,QString)));
//    QObject::connect(&c, SIGNAL(refused(int,int,QString)), &al, SLOT(start(int,int,QString)));
//    QObject::connect(&ac, SIGNAL(refused(int,int,QString)), &al, SLOT(start(int,int,QString)));

    // Connect welcome and admincheck
    QObject::connect(&w, SIGNAL(administor(int)), &ac, SLOT(start(int)));
    QObject::connect(&ac, SIGNAL(back(int)), &w, SLOT(reShow(int)));

    // Connect admincheck and administor
    QObject::connect(&ac, SIGNAL(confirmed(int,QString)), &ad, SLOT(start(int,QString)));

    // Connect administor and cameraget
    QObject::connect(&ad, SIGNAL(catchFace(int,QString)), &c, SLOT(start(int,QString)));

    // Connect cameraget and showfaces
    QObject::connect(&c, SIGNAL(showFaces(int, QString)), &s, SLOT(start(int,QString)));

    // Connect showfaces and administor
    QObject::connect(&s, SIGNAL(back(int)), &ad, SLOT(reShow(int)));

    // Connect administor and welcom
    QObject::connect(&ad, SIGNAL(back(int)), &w, SLOT(reShow(int)));


    return a.exec();
}
