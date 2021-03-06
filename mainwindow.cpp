#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QClipboard>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("Copyright @ Bitdove");
    ui->groupBox->setVisible(false);
    ui->groupBox_2->setVisible(false);
    ui->pushButton_magic->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ok_clicked()
{
   int Pro_typ=0;
   last_choosed_radio_ifPro=choosed_radio_ifPro;

  if(choosed_radio_ifPro==0)//choosed_radio_langge==0)
  { 
      text_out = QString();

     QTextStream stream(&text_in);
     QString line;
     QVector<QString> lines;

     while (stream.readLineInto(&line)) {
         lines.push_back(line);
     }

     if( lines.size() >= 1) {
         text_out.append(lines[0]);
     }

     for( int i = 0; i < lines.size(); i++) {
         // check "  \"
         bool isWrap = false;
         QRegularExpression reg("[ ]+\\\\$");
         int index = 0;
         QRegularExpressionMatch match;
         do{
             match = reg.match(lines[i], index);
             if(match.hasMatch()){
                 index = match.capturedEnd();
                 qDebug() << match.capturedStart() << "," << match.captured(0);
                 isWrap = true;
             } else {
                 break;
             }
         } while (index < lines[i].length());

         // current end with a-Z, next line begin with a-Z
         bool isSpace = false;
         QRegularExpression re("[a-zA-Z]$");
         QRegularExpressionMatch match2 = re.match(lines[i]);
         bool hasMatch = match2.hasMatch();

         if(hasMatch && (i + 1) < lines.size()){
             QRegularExpression re3("[a-zA-Z]$");
             QRegularExpressionMatch match3 = re3.match(lines[i + 1]);
             bool hasMatch3 = match3.hasMatch();
             if(hasMatch3) {
                 isSpace = true;
             }
         }

         if(i < (lines.size() - 1)) {
             if(isWrap) {
                 text_out.append("\n").append(lines[i + 1]);
             } else {
                 if(lines[i].endsWith("\"") && lines[i + 1].startsWith("-")){
                     text_out.append(" ").append(lines[i + 1]);
                 } else {
                     if(isSpace){
                         text_out.append(" ").append(lines[i + 1]);
                     }else{
                         text_out.append(lines[i + 1]);
                     }
                 }
             }
         }

     }


//     text_out=gszl(text_in);
     ui->textEdit_out->setPlainText(text_out);
     QString stemp1 = QString("Input %1???Output %2 from PDF to Bash").arg(text_in.length()).arg(text_out.length());
     ui->statusBar->showMessage(stemp1);
  }
  else if(choosed_radio_ifPro==1)
  {
      Pro_typ=ui->comboBox_trans_type->currentIndex();
      last_Pro_typ=Pro_typ;
      if(Pro_typ==0)
      {
          QString text_out_temp=gszl(text_in);
          text_out_temp.replace(" a"," A").replace(" b"," B").replace(" c"," C").replace(" d"," D").replace(" e"," E").replace(" f"," F");
          text_out_temp.replace(" g"," G").replace(" h"," H").replace(" i"," I").replace(" j"," J").replace(" k"," K").replace(" l"," L").replace(" m"," M");
          text_out_temp.replace(" n"," N").replace(" o"," O").replace(" p"," P").replace(" q"," Q").replace(" r"," R").replace(" s"," S").replace(" t"," T");
          text_out_temp.replace(" u"," U").replace(" v"," V").replace(" w"," W").replace(" x"," X").replace(" y"," Y").replace(" z"," Z");

          text_out_temp.replace("-a","-A").replace("-b","-B").replace("-c","-C").replace("-d","-D").replace("-e","-E").replace("-f","-F");
          text_out_temp.replace("-g","-G").replace("-h","-H").replace("-i","-I").replace("-j","-J").replace("-k","-K").replace("-l","-L").replace("-m","-M");
          text_out_temp.replace("-n","-N").replace("-o","-O").replace("-p","-P").replace("-q","-Q").replace("-r","-R").replace("-s","-S").replace("-t","-T");
          text_out_temp.replace("-u","-U").replace("-v","-V").replace("-w","-W").replace("-x","-X").replace("-y","-Y").replace("-z","-Z");
          QChar tempat0=text_out_temp.at(0);
          text_out_temp.replace(0,1,tempat0.toUpper());
          text_out=text_out_temp;
          ui->textEdit_out->setPlainText(text_out);
          QString stemp1=QString("Input%1???Output%2 xxx").arg(text_in.length()).arg(text_out.length());
          ui->statusBar->showMessage(stemp1);
      }
      else if(Pro_typ==1)
      {
          QString text_out_temp=gszl(text_in);
          text_out=text_out_temp.toLower();
          ui->textEdit_out->setPlainText(text_out);
          QString stemp1=QString("Input%1???Output%2 xxx").arg(text_in.length()).arg(text_out.length());
          ui->statusBar->showMessage(stemp1);
      }
      else if(Pro_typ==2)
      {
          QString text_out_temp=gszl(text_in);
          text_out=text_out_temp.toUpper();
          ui->textEdit_out->setPlainText(text_out);
          QString stemp1=QString("Input%1???Output%2 xxx").arg(text_in.length()).arg(text_out.length());
          ui->statusBar->showMessage(stemp1);
      }
      else if(Pro_typ==3)
      {
          QString text_out_temp=gszl(text_in);
          text_out=QtoB(text_out_temp);
          ui->textEdit_out->setPlainText(text_out);
          QString stemp1=QString("Input%1???Output%2 xxx").arg(text_in.length()).arg(text_out.length());
          ui->statusBar->showMessage(stemp1);
      }
      else if(Pro_typ==4)
      {
          QString text_out_temp=gszl(text_in);
          text_out=BtoQ(text_out_temp);
          ui->textEdit_out->setPlainText(text_out);
          QString stemp1=QString("Input%1???Output%2 xxx").arg(text_in.length()).arg(text_out.length());
          ui->statusBar->showMessage(stemp1);
      }
      else if(Pro_typ==5)
      {
          dialog2.show();
      }

  }


}

void MainWindow::on_pushButton_copy_clicked()
{
    QString tempresult=ui->textEdit_out->toPlainText();
    QClipboard *board = QApplication::clipboard();
    board->setText(tempresult);
    ui->statusBar->showMessage("Result copyed to clipboard.");
}

void MainWindow::on_pushButton_magic_clicked()
{
    QClipboard *board = QApplication::clipboard();
    QString text_in_temp=board->text();
    qint8 Pro_typ1=ui->comboBox_trans_type->currentIndex();

    if(text_in_temp!=text_out)
    {
            text_in=text_in_temp;
            ui->textEdit_in->setPlainText(text_in);
            on_pushButton_ok_clicked();
            on_pushButton_copy_clicked();
    }
    else if(text_in_temp==text_out)
    {
        if(last_choosed_radio_ifPro!=choosed_radio_ifPro||last_choosed_radio_langge!=choosed_radio_langge||last_Pro_typ!=Pro_typ1)
        {
            ui->textEdit_in->setPlainText(text_in);
            on_pushButton_ok_clicked();
            on_pushButton_copy_clicked();
        }

    }

}


void MainWindow::on_textEdit_in_textChanged()
{
    text_in=ui->textEdit_in->toPlainText();
}

void MainWindow::on_textEdit_out_textChanged()
{
    //text_out=ui->textEdit_out->toPlainText();
}

QString MainWindow::gszl(QString strin1)
{
    QString strtemp1=strin1;
    last_choosed_radio_langge=choosed_radio_langge;
    if(choosed_radio_langge==0)  //english
    {
        strtemp1.replace("-\r\n-","").replace("-\n\r-","").replace("-\n-","").replace("-\r-","");
        strtemp1.replace("-\r\n","").replace("-\n\r","").replace("-\n","").replace("-\r","");
        strtemp1.replace("\r\n"," ").replace("\n\r"," ").replace("\n"," ").replace("\r"," ");
        for(int i=1;i<20;i++)
        {
         strtemp1.replace("  "," ");
        }

    }
    else if(choosed_radio_langge==1)   //chinese
    {
       strtemp1.replace("\r\n","").replace("\n\r","").replace("\n","").replace("\r","");
       for(int i=1;i<20;i++)
       {
        strtemp1.replace(" ","");
       }

    }
    else if(choosed_radio_langge==2) //zhongyingwen
    {
        strtemp1.replace("-\r\n","").replace("-\n\r","").replace("-\n","").replace("-\r","");
        strtemp1.replace("\r\n","").replace("\n\r","").replace("\n","").replace("\r","");
        for(int i=1;i<20;i++)
        {
         strtemp1.replace("  "," ");
        }

    }
    return strtemp1;
}

QString MainWindow::QtoB(QString strin1)
{
       QString strin2=strin1;
       strin2.replace("???","a").replace("???","b").replace("???","c").replace("???","d").replace("???","e").replace("???","f").replace("???","g");
       strin2.replace("???","h").replace("???","i").replace("???","j").replace("???","k").replace("???","l").replace("???","m").replace("???","n");
       strin2.replace("???","o").replace("???","p").replace("???","q").replace("???","r").replace("???","s").replace("???","t").replace("???","u");
       strin2.replace("???","v").replace("???","w").replace("???","x").replace("???","y").replace("???","z");

       strin2.replace("???","1").replace("???","2").replace("???","3").replace("???","4").replace("???","5").replace("???","6").replace("???","7");
       strin2.replace("???","8").replace("???","9").replace("???","0").replace("???","[").replace("???","]").replace("???","(").replace("???",")");
       //strin2.replace("???",",").replace("???",".").replace("???",";").replace("???",":").replace("???","<").replace("???",">");
       return strin2;
}

QString MainWindow::BtoQ(QString strin1)
{
    QString strin2=strin1;
    strin2.replace("a","???").replace("b","???").replace("c","???").replace("d","???").replace("e","???").replace("f","???").replace("g","???");
    strin2.replace("h","???").replace("i","???").replace("j","???").replace("k","???").replace("l","???").replace("m","???").replace("n","???");
    strin2.replace("o","???").replace("p","???").replace("q","???").replace("r","???").replace("s","???").replace("t","???").replace("u","???");
    strin2.replace("v","???").replace("w","???").replace("x","???").replace("y","???").replace("z","???");

    strin2.replace("1","???").replace("2","???").replace("3","???").replace("4","???").replace("5","???").replace("6","???").replace("7","???");
    strin2.replace("8","???").replace("9","???").replace("0","???").replace("[","???").replace("]","???").replace("(","???").replace(")","???");
   // strin2.replace(",","???").replace(".","???").replace(";","???").replace(":","???").replace("<","???").replace(">","???");
    return strin2;
}



void MainWindow::on_radioButton_in_eng_clicked()
{
    choosed_radio_langge=0;
}
void MainWindow::on_radioButton_in_chin_clicked()
{
    choosed_radio_langge=1;
}
void MainWindow::on_radioButton_in_chin_eng_clicked()
{
    choosed_radio_langge=2;
}

void MainWindow::on_radioButton_zl_clicked()
{
    choosed_radio_ifPro=0;
    ui->comboBox_trans_type->setEnabled(false);
}

void MainWindow::on_radioButton_transla_clicked()
{
    choosed_radio_ifPro=1;
    ui->comboBox_trans_type->setEnabled(true);
}

void MainWindow::on_pushButton_clear_clicked()
{
    QString temp2="";
    text_in=temp2;
    text_out=temp2;
    ui->textEdit_in->setPlainText(text_in);
    ui->textEdit_out->setPlainText(text_out);
    ui->statusBar->showMessage("Already clear.");
}


