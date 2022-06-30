#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
   // int total_bill=0;

    //open ourdatabase
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:/hungry_naki_db.db");
    db.open();


        segundos = 0;
        minutos = 0;
        pausado = false;
        connect(&reloj,SIGNAL(timeout()),this,SLOT(procesar()));

}

MainWindow::~MainWindow()
{

    db.close();
    delete ui;
}

//if owner button clicked then goto bosshere page
void MainWindow::on_ownerbutton_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}

//if back button clicked then goto first page
void MainWindow::on_pushButton_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}



//----------------------------------------------------------
//Owner Part





//login data matching...
void MainWindow::on_pushButton_login_clicked()
{
    login_username = ui->lineEdit_username->text();
    login_password = ui->lineEdit_password->text();
    // qDebug() << login_username;

    //matching owner login and password;
    QSqlQuery query;
    query.exec("SELECT * FROM ownerLogin WHERE email = '"+login_username+"' AND password = '"+login_password+"'");

    if(query.next()){
        //if match then go to owner profile page.
        ui->stackedWidget->setCurrentIndex(2);

        //show owner profile....
        ui->display_name_show->setText(query.value(0).toString());
        ui->display_email_show->setText(query.value(1).toString());
        ui->display_contact_show->setText(query.value(3).toString());
    }
    else{
        //else show e wrong message.
        QMessageBox::warning(this,"Login failed","Wrong User & Password!!");
    }

    //for clear display data .....
    ui->lineEdit_username->clear();
    ui->lineEdit_password->clear();
}

//adding new member here........
void MainWindow::on_add_member_submit_button_clicked()
{
     QString comboBox_select = ui->select_member_comboBox->currentText();
      //qDebug() << comboBox_select;
     if(comboBox_select=="Owner"){
         add_member_name = ui->add_input_name->text();
         add_member_email = ui->add_input_email->text();
         add_member_password = ui->add_input_password->text();
         add_member_contact = ui->add_input_contact->text();
         QSqlQuery query;
         query.exec("INSERT INTO ownerLogin (name ,email,password,contact) VALUES('"+add_member_name+"','"+add_member_email+"','"+add_member_password+"','"+add_member_contact+"')");

         QMessageBox :: information(this,"Member Info.","Member Added Successful");
     }
     else if(comboBox_select=="Manager"){
         add_member_name = ui->add_input_name->text();
         add_member_email = ui->add_input_email->text();
         add_member_password = ui->add_input_password->text();
         add_member_contact = ui->add_input_contact->text();
         QSqlQuery query;
         query.exec("INSERT INTO managerLogin (name ,email,password,contact) VALUES('"+add_member_name+"','"+add_member_email+"','"+add_member_password+"','"+add_member_contact+"')");

         QMessageBox :: information(this,"Member Info.","Member Added Successful");
     }
     else if(comboBox_select=="Chef"){
         add_member_name = ui->add_input_name->text();
         add_member_email = ui->add_input_email->text();
         add_member_password = ui->add_input_password->text();
         add_member_contact = ui->add_input_contact->text();
         QSqlQuery query;
         query.exec("INSERT INTO chefLogin (name ,email,password,contact) VALUES('"+add_member_name+"','"+add_member_email+"','"+add_member_password+"','"+add_member_contact+"')");

         QMessageBox :: information(this,"Member Info.","Member Added Successful");
     }
     else if(comboBox_select=="Waiter"){
         add_member_name = ui->add_input_name->text();
         add_member_email = ui->add_input_email->text();
         add_member_password = ui->add_input_password->text();
         add_member_contact = ui->add_input_contact->text();
         QSqlQuery query;
         query.exec("INSERT INTO waiterData (name ,email,password,contact) VALUES('"+add_member_name+"','"+add_member_email+"','"+add_member_password+"','"+add_member_contact+"')");

         QMessageBox :: information(this,"Member Info.","Member Added Successful");
     }

      ui->add_input_name->clear();
      ui->add_input_email->clear();
      ui->add_input_password->clear();
      ui->add_input_contact->clear();
}


void MainWindow::on_back_button_bosspage_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_update_button_clicked()
{

    match_username = ui->update_old_email->text();
    match_password = ui->update_old_password->text();
    update_thing = ui->update_e_n_p_c->text();

     //for update purpose matching login data
    QSqlQuery query;
    query.exec("SELECT * FROM ownerLogin WHERE email = '"+match_username+"' AND password = '"+match_password+"'");

      //combox string taken here
     QString upadate_comboBox_select = ui->update_comboBox->currentText();


     //changing name here...
     if(upadate_comboBox_select == "Name" && query.next()==true){
        QSqlQuery qry;
        qry.prepare("update ownerLogin set name = '"+update_thing+"' where email ='"+match_username+"'");
        if(qry.exec()){
        QMessageBox :: information(this,"Update Info.","Updated Successful");
          }
     }

    //changing mail here...
    else if(upadate_comboBox_select == "Email" && query.next()==true){
        QSqlQuery qry;
        qry.prepare("update ownerLogin set email = '"+update_thing+"' where password ='"+match_password+"'");
        if(qry.exec()){
        QMessageBox :: information(this,"Update Info.","Updated Successful");
          }
     }

     //changing password here...
     else if(upadate_comboBox_select == "Password" && query.next()==true){
         QSqlQuery qry;
         qry.prepare("update ownerLogin set password = '"+update_thing+"' where email ='"+match_username+"'");
         if(qry.exec()){
         QMessageBox :: information(this,"Update Info.","Updated Successful");
           }
      }

     //changing contact here...
     else if(upadate_comboBox_select == "Contact" && query.next()==true){
         QSqlQuery qry;
         qry.prepare("update ownerLogin set contact = '"+update_thing+"' where email ='"+match_username+"'");
         if(qry.exec()){
         QMessageBox :: information(this,"Update Info.","Updated Successful");
           }
      }
}


void MainWindow::on_to_see_profile_button_clicked()
{

      QString comboBox_select = ui->comboBox_for_profiles->currentText();

    if(comboBox_select == "Owner"){

       //db.open();

       QSqlQueryModel * modal = new QSqlQueryModel (ui->tableView_profiles);
       modal-> setQuery(QString ("select name,email,contact from ownerLogin "));
       modal->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
       modal->setHeaderData(1, Qt::Horizontal, QObject::tr("Email"));
       modal->setHeaderData(3, Qt::Horizontal, QObject::tr("Contact"));

       ui->tableView_profiles-> setModel(modal);

       //db.close ();
    }
    else if(comboBox_select == "Manager"){
        //db.open();

        QSqlQueryModel * modal = new QSqlQueryModel (ui->tableView_profiles);
        modal-> setQuery(QString ("select name,email,contact from managerLogin "));
        modal->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
        modal->setHeaderData(1, Qt::Horizontal, QObject::tr("Email"));
        modal->setHeaderData(3, Qt::Horizontal, QObject::tr("Contact"));

        ui->tableView_profiles-> setModel(modal);

        //db.close ();
    }
    else if(comboBox_select == "Chef"){
        //db.open();

        QSqlQueryModel * modal = new QSqlQueryModel (ui->tableView_profiles);
        modal-> setQuery(QString ("select name,email,contact from chefLogin "));
        modal->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
        modal->setHeaderData(1, Qt::Horizontal, QObject::tr("Email"));
        modal->setHeaderData(3, Qt::Horizontal, QObject::tr("Contact"));

        ui->tableView_profiles-> setModel(modal);

        //db.close ();
    }
    else if(comboBox_select == "Waiter"){
       // db.open();

        QSqlQueryModel * modal = new QSqlQueryModel (ui->tableView_profiles);
        modal-> setQuery(QString ("select name,email,contact from waiterData "));
        modal->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
        modal->setHeaderData(1, Qt::Horizontal, QObject::tr("Email"));
        modal->setHeaderData(3, Qt::Horizontal, QObject::tr("Contact"));

        ui->tableView_profiles-> setModel(modal);

       // db.close ();
    }
    else if(comboBox_select == "Customer"){
       // db.open();

        QSqlQueryModel * modal = new QSqlQueryModel (ui->tableView_profiles);
        modal-> setQuery(QString ("select name,email,contact from customerLogin "));
        modal->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
        modal->setHeaderData(1, Qt::Horizontal, QObject::tr("Email"));
        modal->setHeaderData(2, Qt::Horizontal, QObject::tr("Contact"));

        ui->tableView_profiles-> setModel(modal);


    }
}



//delete member from database,
void MainWindow::on_delete_confirmed_button_clicked()
{
    match_password = ui->for_member_delete_password->text();
    delete_thing = ui->member_delete->text();

    //db.open();
    //for delete purpose matching login data
   QSqlQuery query;
   query.exec("SELECT * FROM ownerLogin WHERE password = '"+match_password+"'");

     //combox string taken here
    QString delete_comboBox_select = ui->comboBox_for_delete_member->currentText();

    //condition for different data table like owner,manager,chef,waiter
    if(delete_comboBox_select=="Owner"&& query.next()==true){

        QSqlQuery qry;
        qry.prepare("delete from ownerLogin where email = '"+delete_thing+"'");
        if(qry.exec()){
        QMessageBox :: information(this,"Delete Info.","Member Deleted");
          }
    }

    else if(delete_comboBox_select=="Manager"&& query.next()==true){

        QSqlQuery qry;
        qry.prepare("delete from managerLogin where email = '"+delete_thing+"'");
        if(qry.exec()){
        QMessageBox :: information(this,"Delete Info.","Member Deleted");
          }
    }
    else if(delete_comboBox_select=="Chef"&& query.next()==true){

        QSqlQuery qry;
        qry.prepare("delete from chefLogin where email = '"+delete_thing+"'");
        if(qry.exec()){
        QMessageBox :: information(this,"Delete Info.","Member Deleted");
          }
    }
    else if(delete_comboBox_select=="Waiter"&& query.next()==true){

        QSqlQuery qry;
        qry.prepare("delete from waiterData where email = '"+delete_thing+"'");
        if(qry.exec()){
        QMessageBox :: information(this,"Delete Info.","Member Deleted");
          }
    }
   // db.close();
}

//to go owner last page press the button
void MainWindow::on_next_page_button_clicked()
{
     ui->stackedWidget->setCurrentIndex(3);
}

//owner pannel last page to back page
void MainWindow::on_back_button_ownerlastpage_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_owner_logout_button_clicked()
{
  ui->stackedWidget->setCurrentIndex(0);
}


//---------------------------------------------------------------------------------------------
//Manager Part

void MainWindow::on_managerbutton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_manager_back_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_manager_login_button_clicked()
{
        login_username = ui->manager_email_input->text();
        login_password = ui->manager_password_input->text();
        // qDebug() << login_username;

        //matching owner login and password;
        QSqlQuery query;
        query.exec("SELECT * FROM ownerLogin WHERE email = '"+login_username+"' AND password = '"+login_password+"' ");

        //matching manager login and password;
        QSqlQuery query2;
        query2.exec("SELECT * FROM managerLogin WHERE email = '"+login_username+"' AND password = '"+login_password+"' ");

        if(query.next()){
            //if match then go to owner profile page.
            ui->stackedWidget->setCurrentIndex(5);


            //show owner profile....
            ui->manager_profile_name_show->setText(query.value(0).toString());
            ui->manager_profile_email_show->setText(query.value(1).toString());
            ui->manager_profile_password_show->setText(query.value(3).toString());


        }
        else if(query2.next()){
            //if match then go to owner profile page.
            ui->stackedWidget->setCurrentIndex(5);


            //show owner profile....
            ui->manager_profile_name_show->setText(query2.value(0).toString());
            ui->manager_profile_email_show->setText(query2.value(1).toString());
            ui->manager_profile_password_show->setText(query2.value(3).toString());


        }
        else{
            //else show e wrong message.
            QMessageBox::warning(this,"Login failed","Wrong User & Password!!");
        }

        //for clear display data .....
        ui->manager_email_input->clear();
        ui->manager_password_input->clear();
}

//to see menu on manager diplay
void MainWindow::on_manager_menu_show_button_clicked()
{
    //db.open();

    QSqlQueryModel * modal = new QSqlQueryModel (ui->tableView_manager_menu);
    modal-> setQuery(QString ("select foodName ,price,quantity,discount from foodMenu "));
    modal->setHeaderData(0, Qt::Horizontal, QObject::tr("Item Name"));
    modal->setHeaderData(1, Qt::Horizontal, QObject::tr("Price"));
    modal->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantity"));
    modal->setHeaderData(3, Qt::Horizontal, QObject::tr("Discount"));


    ui->tableView_manager_menu-> setModel(modal);

    //db.close ();
}

//adding new item into our database..........
void MainWindow::on_add_item_button_clicked()
{
    add_foodName     = ui->add_food_name->text();
    add_foodPrice    = ui->add_food_price->text();
    add_foodQuantity = ui->add_food_quantity->text();
    add_foodDiscount = ui->add_food_discount->text();
    QSqlQuery query5;
    query5.exec("INSERT INTO foodMenu (foodName ,price,quantity,discount) VALUES('"+add_foodName+"','"+add_foodPrice+"','"+add_foodQuantity+"','"+add_foodDiscount+"')");

    QMessageBox :: information(this,"Menu Info.","Item Added Successful.");


    ui->add_food_name->clear();
    ui->add_food_price->clear();
    ui->add_food_quantity->clear();
    ui->add_food_discount->clear();
}


//edit and Update our menu.................

void MainWindow::on_edit_item_save_button_clicked()
{
    update_thing   = ui->input_for_itemedit->text();
    itemEdit_query = ui->itemEdit_name_input->text();

      //combox string taken here
     QString upadate_comboBox_select = ui->edititem_comboBox->currentText();
    //db.open();

     //changing name here...
     if(upadate_comboBox_select == "Item Name"){
        QSqlQuery qry6;
        qry6.prepare("update foodMenu set foodName = '"+update_thing+"' where foodName = '"+itemEdit_query+"'");
        if(qry6.exec()){
        QMessageBox :: information(this,"Update Info.","Updated Successful");
          }
     }

    else if(upadate_comboBox_select == "Price"){
        QSqlQuery qry6;
        qry6.prepare("update foodMenu set price = '"+update_thing+"' where foodName = '"+itemEdit_query+"'");
        if(qry6.exec()){
        QMessageBox :: information(this,"Update Info.","Updated Successful");
          }
     }
     else if(upadate_comboBox_select == "Quantity"){
         QSqlQuery qry6;
         qry6.prepare("update foodMenu set quantity = '"+update_thing+"' where foodName = '"+itemEdit_query+"'");
         if(qry6.exec()){
         QMessageBox :: information(this,"Update Info.","Updated Successful");
           }
      }
     else if(upadate_comboBox_select == "Discount"){
         QSqlQuery qry6;
         qry6.prepare("update foodMenu set discount = '"+update_thing+"' where foodName = '"+itemEdit_query+"'");
         if(qry6.exec()){
         QMessageBox :: information(this,"Update Info.","Updated Successful");
           }
      }


      ui->input_for_itemedit->clear();
      ui->itemEdit_name_input->clear();

    // db.close();
}

//delete item from the menu

void MainWindow::on_item_delete_button_clicked()
{
        delete_thing = ui->item_delete_input->text();

      //  db.open();

        QSqlQuery qry8;
        qry8.prepare("delete from foodMenu where foodName = '"+delete_thing+"'");
        if(qry8.exec()){
        QMessageBox :: information(this,"Delete Info.","Item Deleted.");
          }
      // db.close();
}


void MainWindow::on_manager_customer_details_button_clicked()
{
    //db.open();

    QSqlQueryModel * modal = new QSqlQueryModel (ui->tableView_manager_menu);
    modal-> setQuery(QString ("select name,email,contact,address from customerLogin "));
    modal->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
    modal->setHeaderData(1, Qt::Horizontal, QObject::tr("Email"));
    modal->setHeaderData(2, Qt::Horizontal, QObject::tr("Contact"));
    modal->setHeaderData(3, Qt::Horizontal, QObject::tr("Address"));


    ui->tableView_manager_menu-> setModel(modal);

   // db.close ();
}


void MainWindow::on_back_button_manager_pannel_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_Logout_button_manager_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_chefbutton_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_chef_back_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}




//===============================================================================================================
//CHEF PART

//chef login..............................................
void MainWindow::on_chef_login_button_clicked()
{
    login_username = ui->chef_email_input->text();
    login_password = ui->chef_password_input->text();
    // qDebug() << login_username;

    //matching owner login and password;
    QSqlQuery query;
    query.exec("SELECT * FROM ownerLogin WHERE email = '"+login_username+"' AND password = '"+login_password+"' ");

    //matching manager login and password;
    QSqlQuery query2;
    query2.exec("SELECT * FROM managerLogin WHERE email = '"+login_username+"' AND password = '"+login_password+"' ");

    QSqlQuery query9;
    query9.exec("SELECT * FROM chefLogin WHERE email = '"+login_username+"' AND password = '"+login_password+"' ");

    if(query.next()){
        //if match then go to owner profile page.
        ui->stackedWidget->setCurrentIndex(7);


        //show owner profile....
        ui->show_chef_name->setText(query.value(0).toString());
        ui->show_chef_email->setText(query.value(1).toString());
        ui->show_chef_contact->setText(query.value(3).toString());


    }
    else if(query2.next()){
        //if match then go to owner profile page.
        ui->stackedWidget->setCurrentIndex(7);


        //show owner profile....
        ui->show_chef_name->setText(query2.value(0).toString());
        ui->show_chef_email->setText(query2.value(1).toString());
        ui->show_chef_contact->setText(query2.value(3).toString());

    }
    else if(query9.next()){
        //if match then go to owner profile page.
        ui->stackedWidget->setCurrentIndex(7);


        //show owner profile....
        ui->show_chef_name->setText(query9.value(0).toString());
        ui->show_chef_email->setText(query9.value(1).toString());
        ui->show_chef_contact->setText(query9.value(3).toString());


    }
    else{
        //else show e wrong message.
        QMessageBox::warning(this,"Login failed","Wrong User & Password!!");
    }

    //for clear display data .....
    ui->chef_email_input->clear();
    ui->chef_password_input->clear();
}


void MainWindow::on_chef_menu_button_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel (ui->chef_tableView);
    modal-> setQuery(QString ("select foodName,price,quantity,discount from foodMenu "));
    modal->setHeaderData(0, Qt::Horizontal, QObject::tr("Item Name"));
    modal->setHeaderData(1, Qt::Horizontal, QObject::tr("Price"));
    modal->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantity"));
    modal->setHeaderData(3, Qt::Horizontal, QObject::tr("Discount"));


    ui->chef_tableView-> setModel(modal);
}


void MainWindow::on_chef_item_update_button_clicked()
{
    update_thing   = ui->chef_quantityEdit_input->text();
    itemEdit_query = ui->chef_itemEdit_input->text();

    QSqlQuery qry11;
    qry11.prepare("update foodMenu set quantity = '"+update_thing+"' where foodName ='"+itemEdit_query+"'");
    if(qry11.exec()){
    QMessageBox :: information(this,"Update Info.","Updated Successful");
      }
    ui->chef_quantityEdit_input->clear();
    ui->chef_itemEdit_input->clear();
}


void MainWindow::on_chef_back_button_2_clicked()
{
     ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_chef_logout_button_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}





//===========================================================================================
//Customer Part HERE......


void MainWindow::on_customerbutton_clicked()
{
     ui->stackedWidget->setCurrentIndex(8);
}


void MainWindow::on_customer_login_button_clicked()
{
    login_username = ui->customer_email_input->text();
    login_password = ui->customer_password_input->text();
    // qDebug() << login_username;

    //matching owner login and password;
    QSqlQuery query12;
    query12.exec("SELECT * FROM customerLogin WHERE email = '"+login_username+"' AND password = '"+login_password+"'");

    if(query12.next()){
        //if match then go to owner profile page.
        ui->stackedWidget->setCurrentIndex(9);

        //show owner profile....
        ui->customer_name->setText(query12.value(0).toString());
       // ui->display_email_show->setText(query.value(1).toString());
       //ui->display_contact_show->setText(query.value(3).toString());
    }
    else{
        //else show e wrong message.
        QMessageBox::warning(this,"Login failed","Wrong User & Password!!");
    }

    //for clear display data .....
    ui->customer_email_input->clear();
    ui->customer_password_input->clear();
}


void MainWindow::on_customer_login_back_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_customer_menu_button_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel (ui->customer_tableView);
    modal-> setQuery(QString ("select foodName,price,quantity,discount from foodMenu "));
    modal->setHeaderData(0, Qt::Horizontal, QObject::tr("Item Name"));
    modal->setHeaderData(1, Qt::Horizontal, QObject::tr("Price"));
    modal->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantity"));
    modal->setHeaderData(3, Qt::Horizontal, QObject::tr("Discount"));


    ui->customer_tableView-> setModel(modal);
}


void MainWindow::on_customer_resister_button_clicked()
{
    add_member_name = ui->customer_signup_name->text();
    add_member_email = ui->customer_signup_email->text();
    add_member_password = ui->customer_signup_password->text();
    add_member_contact = ui->customer_signup_mobile->text();
    customer_address_db = ui->customer_signup_address->text();
    QSqlQuery query13;
    query13.exec("INSERT INTO customerLogin(name,email,password,contact,address) VALUES('"+add_member_name+"','"+add_member_email+"','"+add_member_password+"','"+add_member_contact+"','"+customer_address_db+"')");

    QMessageBox :: information(this,"SignUp Info.","SignUp Successful, Please login.");

          ui->customer_signup_name->clear();
          ui->customer_signup_email->clear();
          ui->customer_signup_password->clear();
          ui->customer_signup_mobile->clear();
          ui->customer_signup_address->clear();
}


void MainWindow::on_customer_back_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}


void MainWindow::on_review_done_button_clicked()
{
    take_review = ui->take_review_input->text();

    QSqlQuery query14;
    query14.exec("INSERT INTO customerReview (review) VALUES('"+take_review+"')");

    QMessageBox :: information(this,"Review Info.","Thank You for your review.");
    ui->take_review_input->clear();
}
void MainWindow::on_customer_next_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
    ui->total_bill_last->setText(total_bill_str);
}
void MainWindow::on_owner_review_button_clicked()
{

    QSqlQueryModel * modal = new QSqlQueryModel (ui->review_tableView);
    modal-> setQuery(QString ("select review from customerReview "));
    modal->setHeaderData(0, Qt::Horizontal, QObject::tr("Customer Review Here"));



    ui->review_tableView-> setModel(modal);

}


void MainWindow::on_c2_back_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}


void MainWindow::on_customer_logout_button_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}

//customer order save to my data base
void MainWindow::on_customer_order_button_clicked()
{

    //take order input here.
    order_table    = ui->table_number_input->text();
    order_item_no  = ui->item_number_input->text();
    order_quantity = ui->item_number_quantity->text();



    //query for item name know
    QSqlQuery query17;
    query17.exec("SELECT * FROM foodMenu WHERE itemcode = '"+order_item_no+"' ");

    if(query17.next()){
        order_item_name=query17.value(0).toString();

        //---------------------------------------
        //         Billing
        //---------------------------------------

        int item_price,item_quantity,bill,previous_quantity_int,discount_int;


        //take previous quantity from table
        previous_quantity_int = query17.value(2).toInt();


        //discount take
        discount_int = query17.value(3).toInt();


        //peice convert
        item_price = query17.value(1).toInt();
        item_price_str = query17.value(1).toString();

        //quantity convert
        item_quantity= order_quantity.toInt();
        item_quantity_str = order_quantity;
        //qDebug() << item_price;

        if(previous_quantity_int<item_quantity||item_quantity<=0){
             QMessageBox :: information(this,"Quantity Error.","Sorry Check quantity.");
        }
        else{
        //decrease the quantity here,
        previous_quantity_int =previous_quantity_int - item_quantity;
        update_thing=QString::number(previous_quantity_int);

        //biling here
        item_price -= ((item_price*discount_int)/100);
        bill=(item_price*item_quantity);
        bill_str = QString::number(bill);
        total_bill+=bill;


        //discount calculate here...
        discount_int=item_quantity*(item_price*discount_int)/100;
        //qDebug() << discount_int;
        discount_str = QString::number(discount_int);




    QSqlQuery q;
    q.exec("INSERT INTO customerOrder(item_name,quantity,table_no,price,billing,discount) VALUES('"+order_item_name+"','"+order_quantity+"','"+order_table+"','"+item_price_str+"','"+ bill_str+"','"+discount_str+"')");
    //query18.exec("INSERT INTO customersBill (table,item_name,price,quantity,billing) VALUES('"+order_table+"','"+order_item_name+"','"+item_price_str+"','"+item_quantity_str+"','"+bill_str+"')");

   QMessageBox :: information(this,"Order Info.","Order confirmed.");
        }

}
    QSqlQuery q2;
    q2.prepare("update foodMenu set quantity = '"+update_thing+"' where foodName ='"+order_item_name+"'");
       //qDebug() << update_thing;

       if(q2.exec()){}






        //for clear display data .....
        //ui->table_number_input->clear();
        ui->item_number_input->clear();
        ui->item_number_quantity->clear();
}

//Chef see customer orders here
void MainWindow::on_chef_see_order_button_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel (ui->chef_tableView);
    modal-> setQuery(QString ("select item_name ,quantity,table_no,verdict from customerOrder "));
    modal->setHeaderData(0, Qt::Horizontal, QObject::tr("Item Name"));
    modal->setHeaderData(1, Qt::Horizontal, QObject::tr("Quantity"));
    modal->setHeaderData(2, Qt::Horizontal, QObject::tr("Table No"));
    modal->setHeaderData(3, Qt::Horizontal, QObject::tr("Verdict"));


    ui->chef_tableView-> setModel(modal);
}

//if food made by chef then chef upadate it by writing done
void MainWindow::on_chef_verdict_button_clicked()
{
    match_serial = ui->chef_order_no_input->text();
    update_thing = ui->chef_order_verdict->text();
    //serial_int = match_serial.toInt();
    //int number ;
   // number = match_serial.toInt();

    //bool ok;
    //int number= match_serial.toInt(&ok);
   // if (!ok) {
   //   qDebug() << "Conversion failed. Repeat conversion";
   // }

    QSqlQuery query18;
    query18.prepare("update customerOrder set verdict = '"+update_thing+"' WHERE order_no = CAST("+match_serial+" as INT) ");
    if(query18.exec()){
    QMessageBox :: information(this,"Update Info.","Updated Successful");
      }

    ui->chef_order_no_input->clear();

}


void MainWindow::on_cuntomer_bill_show_clicked()
{


    QSqlQueryModel * modal = new QSqlQueryModel (ui->customer_tableView);
    modal-> setQuery(QString ("select item_name,quantity,price,discount,billing from customerOrder "));
    modal->setHeaderData(0, Qt::Horizontal, QObject::tr("Item"));
    modal->setHeaderData(1, Qt::Horizontal, QObject::tr("Quantity"));
    modal->setHeaderData(2, Qt::Horizontal, QObject::tr("Price"));
    modal->setHeaderData(3, Qt::Horizontal, QObject::tr("Discount"));
    modal->setHeaderData(4, Qt::Horizontal, QObject::tr("Bill"));


    ui->customer_tableView-> setModel(modal);

     //qDebug()<<total_bill;
     total_bill_str = QString::number(total_bill);
     ui->total_bill_out->setText(total_bill_str);


}


void MainWindow::on_pay_button_donate_change_clicked()
{

    Trxid       = ui->donate_change_input->text();
    order_table = ui->donate_table_no->text();
    pay_money   = ui->money_donate->text();
    QMessageBox :: information(this,"Paied Info.","Thank you for your contribution.");

    QString bill_comboBox = ui->donate_comboBox->currentText();
    int donate_int,pay_money_int;
    pay_money_int=pay_money.toInt();

    donate_int= pay_money_int-total_bill;
    update_thing  =  QString::number(donate_int);

    temp="0";

    QSqlQuery q99;
    q99.exec("INSERT INTO bill_history(billTable,trxid,bill,donate,media,change)VALUES('"+order_table+"','"+Trxid+"','"+total_bill_str+"','"+update_thing+"','"+bill_comboBox+"','"+temp+"')");


   total_bill=0;


    ui->donate_change_input->clear();
    ui->donate_table_no->clear();
    ui->money_donate->clear();
}


void MainWindow::on_pay_button_back_change_clicked()
{
    Trxid = ui->change_back_input->text();
    order_table = ui->money_back_table->text();
    pay_money   = ui->back_money->text();

    QMessageBox :: information(this,"Paied Info.","Paied Successful.");
    QString bill_back_comboBox = ui->change_back_comboBox->currentText();


    int remain_int,pay_money_int;
    pay_money_int=pay_money.toInt();

    remain_int= pay_money_int-total_bill;
    update_thing  =  QString::number(remain_int);
    temp="0";


    ui->return_money->setText( update_thing);




    QSqlQuery q98;
    q98.exec("INSERT INTO bill_history(billTable,trxid,bill,donate,media,change)VALUES('"+order_table+"','"+Trxid+"','"+total_bill_str+"','"+temp+"','"+bill_back_comboBox+"','"+update_thing+"')");



     total_bill=0;


    ui->change_back_input->clear();
    ui->money_back_table->clear();
    ui->back_money->clear();
}


void MainWindow::on_pushButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(11);
}


void MainWindow::on_back_homepage_clicked()
{
     ui->stackedWidget->setCurrentIndex(10);
}


void MainWindow::on_homepage_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_manager_bill_see_customer_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel (ui->tableView_manager_menu);
    modal-> setQuery(QString ("select billTable,trxid,bill,media,change from bill_history "));
    modal->setHeaderData(0, Qt::Horizontal, QObject::tr("Table"));
    modal->setHeaderData(1, Qt::Horizontal, QObject::tr("TrxdID"));
    modal->setHeaderData(2, Qt::Horizontal, QObject::tr("Bill"));
    modal->setHeaderData(3, Qt::Horizontal, QObject::tr("Media"));
     modal->setHeaderData(4, Qt::Horizontal, QObject::tr("Back"));


    ui->tableView_manager_menu-> setModel(modal);
}


//=========================================================
// food challange timer stopwatch...........


//start
void MainWindow::on_start_button_clicked()
{
     reloj.start(1000);
}

//stop
void MainWindow::on_stop_button_clicked()
{
       minutos=0;
       segundos=0;
       pausado=false;
       ui->minutos->display(minutos);
       ui->segundos->display(segundos);
       reloj.stop();
}

//pause
void MainWindow::on_pause_button_clicked()
{
    if (pausado==false) {
           reloj.stop();
           pausado=true;
           ui->pause_button->setText("resume");
       }
       else{
           pausado=false;
           reloj.start(1000);
           ui->pause_button->setText("pause");
       }
}

void MainWindow::procesar()
{
    segundos=segundos+1; // segundos++;
       if (segundos==60) {
           segundos=0;
           minutos=minutos+1;
       }
       else{
           ui->segundos->display(segundos);
           ui->minutos->display(minutos);
       }
}


void MainWindow::on_food_challange_button_clicked()
{
     ui->stackedWidget->setCurrentIndex(12);
}


void MainWindow::on_food_challange_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}

