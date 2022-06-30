#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include<QMessageBox>
#include<QSqlDatabase>
#include<QSqlQuery>
#include <QComboBox>
#include <QTableView>
#include <QSqlQueryModel>
#include <QIntValidator>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ownerbutton_clicked();

    void on_pushButton_back_clicked();

    void on_pushButton_login_clicked();

    void on_add_member_submit_button_clicked();

    void on_back_button_bosspage_clicked();

    void on_update_button_clicked();

    void on_to_see_profile_button_clicked();

    void on_delete_confirmed_button_clicked();

    void on_next_page_button_clicked();

    void on_back_button_ownerlastpage_clicked();

    void on_owner_logout_button_clicked();



    void on_managerbutton_clicked();

    void on_manager_back_button_clicked();

    void on_manager_login_button_clicked();

    void on_manager_menu_show_button_clicked();

    void on_add_item_button_clicked();

    void on_edit_item_save_button_clicked();

    void on_item_delete_button_clicked();

    void on_manager_customer_details_button_clicked();

    void on_back_button_manager_pannel_clicked();

    void on_Logout_button_manager_clicked();

    void on_chefbutton_clicked();

    void on_chef_back_button_clicked();

    void on_chef_login_button_clicked();

    void on_chef_menu_button_clicked();

    void on_chef_item_update_button_clicked();

    void on_chef_back_button_2_clicked();

    void on_chef_logout_button_clicked();

    void on_customerbutton_clicked();

    void on_customer_login_button_clicked();

    void on_customer_login_back_button_clicked();

    void on_customer_menu_button_clicked();

    void on_customer_resister_button_clicked();

    void on_customer_back_button_clicked();

    void on_review_done_button_clicked();

    void on_customer_next_button_clicked();

    void on_owner_review_button_clicked();

    void on_c2_back_button_clicked();

    void on_customer_logout_button_clicked();

    void on_customer_order_button_clicked();

    void on_chef_see_order_button_clicked();

    void on_chef_verdict_button_clicked();

    void on_cuntomer_bill_show_clicked();

    void on_pay_button_donate_change_clicked();

    void on_pay_button_back_change_clicked();

    void on_pushButton_clicked();

    void on_back_homepage_clicked();

    void on_homepage_clicked();

    void on_manager_bill_see_customer_clicked();

    void on_start_button_clicked();

    void on_stop_button_clicked();

    void on_pause_button_clicked();

     void procesar();

     void on_food_challange_button_clicked();

     void on_food_challange_back_clicked();

private:
    Ui::MainWindow *ui;
    QString login_username,login_password,comboBox_select;
    QString add_member_name,add_member_email,add_member_password,add_member_contact;
    QString upadate_comboBox_select,update_thing, match_username, match_password;
    QString delete_thing,itemEdit_query,customer_address_db,take_review;
    QString add_foodName,add_foodPrice,add_foodQuantity,add_foodDiscount;
    QString order_table,order_item_name,match_serial,temp;
    QString order_item_no,order_quantity,Trxid,previous_item_quantity;
    QString item_price_str,item_quantity_str,bill_str,total_bill_str;
    QString discount_str,pay_money;
   // qint32 serial_int;
    QSqlDatabase db;
    int total_bill=0;
       short int minutos;
       short int segundos;
       bool pausado;
       QTimer reloj;

};
#endif // MAINWINDOW_H
