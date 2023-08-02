#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QClipboard>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->statusBar->showMessage("Copyright @ Bitdove");
  ui->groupBox->setVisible(false);
  ui->groupBox_2->setVisible(false);
  ui->groupBox->hide();
  ui->groupBox_2->hide();
  ui->pushButton_magic->setVisible(false);
  ui->pushButton_clear->setVisible(false);
  ui->pushButton_ok->setVisible(false);
  ui->pushButton_copy->setVisible(false);
  ui->pushButton_magic->setHidden(true);
  ui->pushButton_clear->setHidden(true);
  ui->pushButton_ok->setHidden(true);
  ui->pushButton_copy->setHidden(true);
  ui->pushButton_magic->hide();
  ui->pushButton_clear->hide();
  ui->pushButton_ok->hide();
  ui->pushButton_copy->hide();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_ok_clicked() {
  int Pro_typ = 0;
  last_choosed_radio_ifPro = choosed_radio_ifPro;

  if (choosed_radio_ifPro == 0) // choosed_radio_langge==0)
  {
    text_out = QString();

    QTextStream stream(&text_in);
    QString line;
    QVector<QString> lines;

    while (stream.readLineInto(&line)) {
      lines.push_back(line);
    }

    if (lines.size() >= 1) {
      text_out.append(lines[0]);
    }

    for (int i = 1; i < lines.size(); i++) {
      // n -1 line end with 0-Z, n line begin with 0-Z.
      static QRegularExpression regEnd("[0-9a-zA-Z]$");
      QRegularExpressionMatch matchEnd = regEnd.match(lines[i - 1]);
      bool hasMatchEnd = matchEnd.hasMatch();
      static QRegularExpression regStart("^[0-9a-zA-Z]");
      QRegularExpressionMatch matchStart = regStart.match(lines[i]);
      bool hasMatchStart = matchStart.hasMatch();

      if (hasMatchEnd && hasMatchStart) {
        text_out.append(" " + lines[i]);
        continue;
      }

      // line begin '"'
      static QRegularExpression regStartDQ("^\"");
      QRegularExpressionMatch matchStartDQ = regStartDQ.match(lines[i]);
      bool hasMatchStartDQ = matchStartDQ.hasMatch();

      if (hasMatchEnd && hasMatchStartDQ) {
        text_out.append(" " + lines[i]);
        continue;
      }

      // line begin '.'
      static QRegularExpression regStartDot("^\.");
      QRegularExpressionMatch matchStartDot = regStartDot.match(lines[i]);
      bool hasMatchStartDot = matchStartDot.hasMatch();

      if (hasMatchEnd && hasMatchStartDot) {
        text_out.append(lines[i]);
        continue;
      }

      // 1 line 1 \ char
      if(lines[i].size() == 1 && lines[i] == '\\') {
        text_out.append(" " + lines[i]);
        continue;
      }

      // default
      text_out.append("\n" + lines[i]);

      int dbg = 0;
      dbg = 1;

      //      if (hasMatch && (i + 1) < lines.size()) {
      //        QRegularExpression re3("[a-zA-Z]$");
      //        QRegularExpressionMatch match3 = re3.match(lines[i + 1]);
      //        bool hasMatch3 = match3.hasMatch();
      //        if (hasMatch3) {
      //          isSpace = true;
      //        }
      //      }

      //      if (!lines[i - 1].endsWith(' ') && !lines[i - 1].endsWith('\r') &&
      //      !lines[i - 1].endsWith('\n') && !lines[i].endsWith('\\')) {
      //        text_out.append(" " + lines[i]);
      //        continue;
      //      }

      // check "  \"
      //      bool isWrap = false;
      //      QRegularExpression reg("[ ]+\\\\$");
      //      int index = 0;
      //      QRegularExpressionMatch match;
      //      do {
      //        match = reg.match(lines[i], index);
      //        if (match.hasMatch()) {
      //          index = match.capturedEnd();
      //          qDebug() << match.capturedStart() << "," << match.captured(0);
      //          isWrap = true;
      //        } else {
      //          break;
      //        }
      //      } while (index < lines[i].length());

      //      // current end with a-Z, next line begin with a-Z
      //      bool isSpace = false;
      //      QRegularExpression re("[a-zA-Z]$");
      //      QRegularExpressionMatch match2 = re.match(lines[i]);
      //      bool hasMatch = match2.hasMatch();

      //      if (hasMatch && (i + 1) < lines.size()) {
      //        QRegularExpression re3("[a-zA-Z]$");
      //        QRegularExpressionMatch match3 = re3.match(lines[i + 1]);
      //        bool hasMatch3 = match3.hasMatch();
      //        if (hasMatch3) {
      //          isSpace = true;
      //        }
      //      }

      //      if (i < (lines.size() - 1)) {
      //        if (isWrap) {
      //          text_out.append("\n").append(lines[i + 1]);
      //        } else {
      //          if (lines[i].endsWith("\"") && lines[i + 1].startsWith("-")) {
      //            text_out.append(" ").append(lines[i + 1]);
      //          } else {
      //            if (isSpace) {
      //              text_out.append(" ").append(lines[i + 1]);
      //            } else {
      //              text_out.append(lines[i + 1]);
      //            }
      //          }
      //        }
      //      }
    }

    //    text_out=gszl(text_in);
    ui->textEdit_out->setPlainText(text_out);
    QString stemp1 = QString("Input %1，Output %2 from PDF to Bash")
                         .arg(text_in.length())
                         .arg(text_out.length());
    ui->statusBar->showMessage(stemp1);
  }
}

void MainWindow::on_pushButton_copy_clicked() {
  QString tempresult = ui->textEdit_out->toPlainText();
  QClipboard *board = QApplication::clipboard();
  board->setText(tempresult);
  ui->statusBar->showMessage("Result copyed to clipboard.");
}

void MainWindow::on_pushButton_magic_clicked() {
  QClipboard *board = QApplication::clipboard();
  QString text_in_temp = board->text();
  qint8 Pro_typ1 = ui->comboBox_trans_type->currentIndex();

  if (text_in_temp != text_out) {
    text_in = text_in_temp;
    ui->textEdit_in->setPlainText(text_in);
    on_pushButton_ok_clicked();
    on_pushButton_copy_clicked();
  } else if (text_in_temp == text_out) {
    if (last_choosed_radio_ifPro != choosed_radio_ifPro ||
        last_choosed_radio_langge != choosed_radio_langge ||
        last_Pro_typ != Pro_typ1) {
      ui->textEdit_in->setPlainText(text_in);
      on_pushButton_ok_clicked();
      on_pushButton_copy_clicked();
    }
  }
}

void MainWindow::on_textEdit_in_textChanged() {
  text_in = ui->textEdit_in->toPlainText();
  on_pushButton_ok_clicked();
  on_pushButton_copy_clicked();
}

void MainWindow::on_textEdit_out_textChanged() {
  // text_out=ui->textEdit_out->toPlainText();
}

QString MainWindow::gszl(QString strin1) {
  QString strtemp1 = strin1;
  last_choosed_radio_langge = choosed_radio_langge;
  if (choosed_radio_langge == 0) // english
  {
    strtemp1.replace("-\r\n-", "")
        .replace("-\n\r-", "")
        .replace("-\n-", "")
        .replace("-\r-", "");
    strtemp1.replace("-\r\n", "")
        .replace("-\n\r", "")
        .replace("-\n", "")
        .replace("-\r", "");
    strtemp1.replace("\r\n", " ")
        .replace("\n\r", " ")
        .replace("\n", " ")
        .replace("\r", " ");
    for (int i = 1; i < 20; i++) {
      strtemp1.replace("  ", " ");
    }

  } else if (choosed_radio_langge == 1) // chinese
  {
    strtemp1.replace("\r\n", "")
        .replace("\n\r", "")
        .replace("\n", "")
        .replace("\r", "");
    for (int i = 1; i < 20; i++) {
      strtemp1.replace(" ", "");
    }

  } else if (choosed_radio_langge == 2) // zhongyingwen
  {
    strtemp1.replace("-\r\n", "")
        .replace("-\n\r", "")
        .replace("-\n", "")
        .replace("-\r", "");
    strtemp1.replace("\r\n", "")
        .replace("\n\r", "")
        .replace("\n", "")
        .replace("\r", "");
    for (int i = 1; i < 20; i++) {
      strtemp1.replace("  ", " ");
    }
  }
  return strtemp1;
}

QString MainWindow::QtoB(QString strin1) {
  QString strin2 = strin1;
  strin2.replace("ａ", "a")
      .replace("ｂ", "b")
      .replace("ｃ", "c")
      .replace("ｄ", "d")
      .replace("ｅ", "e")
      .replace("ｆ", "f")
      .replace("ｇ", "g");
  strin2.replace("ｈ", "h")
      .replace("ｉ", "i")
      .replace("ｊ", "j")
      .replace("ｋ", "k")
      .replace("ｌ", "l")
      .replace("ｍ", "m")
      .replace("ｎ", "n");
  strin2.replace("ｏ", "o")
      .replace("ｐ", "p")
      .replace("ｑ", "q")
      .replace("ｒ", "r")
      .replace("ｓ", "s")
      .replace("ｔ", "t")
      .replace("ｕ", "u");
  strin2.replace("ｖ", "v")
      .replace("ｗ", "w")
      .replace("ｘ", "x")
      .replace("ｙ", "y")
      .replace("ｚ", "z");

  strin2.replace("１", "1")
      .replace("２", "2")
      .replace("３", "3")
      .replace("４", "4")
      .replace("５", "5")
      .replace("６", "6")
      .replace("７", "7");
  strin2.replace("８", "8")
      .replace("９", "9")
      .replace("０", "0")
      .replace("［", "[")
      .replace("］", "]")
      .replace("（", "(")
      .replace("）", ")");
  // strin2.replace("，",",").replace("．",".").replace("；",";").replace("：",":").replace("＜","<").replace("＞",">");
  return strin2;
}

QString MainWindow::BtoQ(QString strin1) {
  QString strin2 = strin1;
  strin2.replace("a", "ａ")
      .replace("b", "ｂ")
      .replace("c", "ｃ")
      .replace("d", "ｄ")
      .replace("e", "ｅ")
      .replace("f", "ｆ")
      .replace("g", "ｇ");
  strin2.replace("h", "ｈ")
      .replace("i", "ｉ")
      .replace("j", "ｊ")
      .replace("k", "ｋ")
      .replace("l", "ｌ")
      .replace("m", "ｍ")
      .replace("n", "ｎ");
  strin2.replace("o", "ｏ")
      .replace("p", "ｐ")
      .replace("q", "ｑ")
      .replace("r", "ｒ")
      .replace("s", "ｓ")
      .replace("t", "ｔ")
      .replace("u", "ｕ");
  strin2.replace("v", "ｖ")
      .replace("w", "ｗ")
      .replace("x", "ｘ")
      .replace("y", "ｙ")
      .replace("z", "ｚ");

  strin2.replace("1", "１")
      .replace("2", "２")
      .replace("3", "３")
      .replace("4", "４")
      .replace("5", "５")
      .replace("6", "６")
      .replace("7", "７");
  strin2.replace("8", "８")
      .replace("9", "９")
      .replace("0", "０")
      .replace("[", "［")
      .replace("]", "］")
      .replace("(", "（")
      .replace(")", "）");
  // strin2.replace(",","，").replace(".","．").replace(";","；").replace(":","：").replace("<","＜").replace(">","＞");
  return strin2;
}

void MainWindow::on_radioButton_in_eng_clicked() { choosed_radio_langge = 0; }
void MainWindow::on_radioButton_in_chin_clicked() { choosed_radio_langge = 1; }
void MainWindow::on_radioButton_in_chin_eng_clicked() {
  choosed_radio_langge = 2;
}

void MainWindow::on_radioButton_zl_clicked() {
  choosed_radio_ifPro = 0;
  ui->comboBox_trans_type->setEnabled(false);
}

void MainWindow::on_radioButton_transla_clicked() {
  choosed_radio_ifPro = 1;
  ui->comboBox_trans_type->setEnabled(true);
}

void MainWindow::on_pushButton_clear_clicked() {
  QString temp2 = "";
  text_in = temp2;
  text_out = temp2;
  ui->textEdit_in->setPlainText(text_in);
  ui->textEdit_out->setPlainText(text_out);
  ui->statusBar->showMessage("Already clear.");
}
