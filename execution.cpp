/*
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <occi.h>
#include <iomanip>
#include <string>
using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

// ASSIGNMENT - 1  =============================================================================================

void Repotr1(string constr, string pass, string user, Environment* env, Connection* conn) {

	try {
		env = Environment::createEnvironment(Environment::DEFAULT);
		// environment scope starts
		conn = env->createConnection(user, pass, constr);
		cout << endl << "Stores in mall report *********************************************************************************" <<
			endl
			<< "MALL ID      MALL NAME MALL                 ADDRESS                   STORE NAME        CONTACT NAME " << endl
			<< "-------  ---------------------     --------------------------     -----------------   ----------------" << endl;
		// call method createStatement() to create an statement object
		Statement* stmt1 = conn->createStatement("SELECT m.mallid, m.mallname, m.malladdress, s.storename, s.storecontactname FROM prj_malldetails m INNER JOIN prj_store s ON m.mallid = s.mallid ORDER BY m.mallid, m.mallname");
		// define a reference to an object resultset
		ResultSet* rs1 = stmt1->executeQuery();
		if (!rs1->next()) {
			// if the result set is empty
			cout << "ResultSet is empty." << endl;
		}
		else {
			do {
				cout << left << setw(10) << rs1->getInt(1)
					<< left << setw(25) << rs1->getString(2)
					<< left << setw(32) << rs1->getString(3)
					<< left << setw(20) << rs1->getString(4)
					<< left << setw(20) << rs1->getString(5) << endl;
			} while (rs1->next());
		}
		env->terminateConnection(conn);
		cout << endl;
		// environment scope ends
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}

}
void Repotr2(string constr, string pass, string user, Environment* env, Connection* conn) {

	try {
		env = Environment::createEnvironment(Environment::DEFAULT);
		// environment scope starts
		conn = env->createConnection(user, pass, constr);
		cout << endl << "Inventory list in stores report *************************************************" << endl
			<< "STORE ID        STORE NAME        STOCK          PRODUCT NAME      PRODUCTCOST " << endl
			<< "----------    ---------------   ---------       -----------------  ------------\n" << endl;
		// call method createStatement() to create an statement object
		Statement* stmt1 = conn->createStatement("SELECT s.storeid, s.storename, i.prodquantity, i.proddescription, i.prodcost FROM prj_store s INNER JOIN prj_inventory i ON s.storeid = i.storeid ORDER BY s.storeid");
		// define a reference to an object resultset
		ResultSet* rs1 = stmt1->executeQuery();
		if (!rs1->next()) {
			// if the result set is empty
			cout << "ResultSet is empty." << endl;
		}
		else {
			do {
				cout << left << setw(15) << rs1->getString(1)
					<< left << setw(20) << rs1->getString(2)
					<< left << setw(15) << rs1->getString(3)
					<< left << setw(20) << rs1->getString(4)
					<< left << setw(20) << rs1->getString(5) << endl;
			} while (rs1->next());
		}
		env->terminateConnection(conn);
		cout << endl;
		// environment scope ends
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}

}
void Repotr3(string constr, string pass, string user, Environment* env, Connection* conn) {

	try {
		env = Environment::createEnvironment(Environment::DEFAULT);
		// environment scope starts
		conn = env->createConnection(user, pass, constr);
		cout << endl << " Employees working in stores report ***********************************************\n" << endl
			<< "STORE ID         NAME            EMPLOYEE ID      EMPLOYEE NAME        POSITION " << endl
			<< "----------    ---------------    -----------     ----------------    ---------------\n" << endl;
		// call method createStatement() to create an statement object
		Statement* stmt2 = conn->createStatement("SELECT s.storeid, s.storename, e.empid, concat(concat(e.empfirstname,' '),e. emplastname), e.empdesignation FROM prj_store s JOIN prj_employees e ON s.storeid = e.storeid ORDER BY s.storeid");
		// define a reference to an object resultset
		ResultSet* rs2 = stmt2->executeQuery();
		if (!rs2->next()) {
			// if the result set is empty
			cout << "ResultSet is empty." << endl;
		}
		else {
			do {
				cout << left << setw(15) << rs2->getString(1)
					<< left << setw(20) << rs2->getString(2)
					<< left << setw(15) << rs2->getString(3)
					<< left << setw(20) << rs2->getString(4)
					<< left << setw(20) << rs2->getString(5) << endl;
			} while (rs2->next());
		}
		env->terminateConnection(conn);
		cout << endl;
		// environment scope ends
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}

}
void dataReports(string constr, string pass, string user, Environment* env, Connection* conn) {
	int choice = 1;
	while (choice != 0)
	{
		cout << "Choose which report to display ?" << endl
			<< " 0. Go Back" << endl
			<< " 1. Stores in mall report" << endl
			<< " 2. Inventory list in stores report" << endl
			<< " 3. Employees working in stores report" << endl
			<< "Enter choice : ";
		cin >> choice;
		switch (choice)
		{
		case 0:
			cout << "GO Back" << endl << endl;
			break;
		case 1:
			Repotr1(constr, pass, user, env, conn);
			break;
		case 2:
			Repotr2(constr, pass, user, env, conn);
			break;
		case 3:
			Repotr3(constr, pass, user, env, conn);
		default:
			cout << "invalid Choice" << endl;
			break;
		}
	}
}


// ASSIGNMENT - 2  =============================================================================================

// these 4 procedures are done by Jashanpreet ==================================================================
void createNewStore(string constr, string pass, string user, Environment* env, Connection* conn) {
	try {

		std::string storeID, storeName, storeContactName, storeMail, storeType;
		int mallID, storePhone, err = 0;

		cout << "Enter Store ID (Mxxx-Sxxx) : "; cin >> storeID;
		cout << "Enter mall ID  (1-7) : "; cin >> mallID;
		cout << "Enter Store Name : "; cin >> storeName;
		cout << "Enter Store Contact Name : "; cin >> storeContactName;
		cout << "Enter Store Phone (0000000000) : "; cin >> storePhone;
		cout << "Enter Store Mail (Storename@example.com) : "; cin >> storeMail;
		cout << "Enter Store Type : "; cin >> storeType;

		env = Environment::createEnvironment(Environment::DEFAULT);
		// environment scope starts
		conn = env->createConnection(user, pass, constr);


		// call method createStatement() to create an statement object
		Statement* stmt = conn->createStatement();
		stmt->setSQL("BEGIN SPPRJ_STOREINSERT(:1, :2, :3, :4, :5, :6, :7, :8); END;");
		stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
		stmt->setString(2, storeID);
		stmt->setInt(3, mallID);
		stmt->setString(4, storeName);
		stmt->setString(5, storeContactName);
		stmt->setInt(6, storePhone);
		stmt->setString(7, storeMail);
		stmt->setString(8, storeType);

		stmt->executeUpdate();
		err = stmt->getInt(1);

		if (err > 0) {
			cout << endl << err << " store inserted Successfully !!" << endl;
		}
		else
		{
			cout << endl << "ERROR : store could not be inserted. The entered StoreID may already exsists. " << endl;
		}

		conn->terminateStatement(stmt);

		env->terminateConnection(conn);
		cout << endl;
		// environment scope ends
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}
void deleteStore(string constr, string pass, string user, Environment* env, Connection* conn) {
	try {

		std::string storeID;
		int err = 0;

		cout << "Enter Store ID (Mxxx-Sxxx) of store that you want to Delete: "; cin >> storeID;

		env = Environment::createEnvironment(Environment::DEFAULT);
		// environment scope starts
		conn = env->createConnection(user, pass, constr);

		// call method createStatement() to create an statement object
		Statement* stmt = conn->createStatement();
		stmt->setSQL("BEGIN spPRJ_StoreDelete(:1, :2); END;");
		stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
		stmt->setString(2, storeID);

		stmt->executeUpdate();
		err = stmt->getInt(1);

		if (err > 0) {
			cout << endl << err << " store with storeID : " << storeID << " Deleted Successfully !!" << endl;
		}
		else if (err == -1)
		{
			cout << endl << "ERROR : The entered StoreID : " << storeID << " does not exsists. " << endl;
		}
		else {
			cout << endl << "ERROR : store could not be Deleted. " << endl;
		}

		conn->terminateStatement(stmt);

		env->terminateConnection(conn);
		cout << endl;
		// environment scope ends
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}
void updateStoreContactName(string constr, string pass, string user, Environment* env, Connection* conn) {
	try {

		std::string storeID, storeContactName;
		int err = 0;

		cout << "Enter Store ID (Mxxx-Sxxx) whose contact Name you wish to update: "; cin >> storeID;
		cout << "Enter New contact Name : "; cin >> storeContactName;

		env = Environment::createEnvironment(Environment::DEFAULT);
		// environment scope starts
		conn = env->createConnection(user, pass, constr);

		// call method createStatement() to create an statement object
		Statement* stmt = conn->createStatement();
		stmt->setSQL("BEGIN PSPRJ_STOREUPDATE(:1, :2, :3); END;");
		stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
		stmt->setString(2, storeID);
		stmt->setString(3, storeContactName);
		stmt->executeUpdate();
		err = stmt->getInt(1);

		if (err > 0) {
			cout << endl << " Contact Name updated to " << storeContactName << " of store with storeID : " << storeID << endl;
		}
		else if (err == -1)
		{
			cout << endl << "ERROR : The entered StoreID : " << storeID << " does not exsists. " << endl;
		}
		else {
			cout << endl << "ERROR : Contact Name could not be updated. " << endl;
		}

		conn->terminateStatement(stmt);

		env->terminateConnection(conn);
		cout << endl;
		// environment scope ends
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}
void selectStore(string constr, string pass, string user, Environment* env, Connection* conn) {
	try {
		int mallID, phone, err = 0;
		std::string storeID, storeName, storeContactName, storeMail, storeType;

		cout << "Enter Store ID to see detils: "; cin >> storeID;

		env = Environment::createEnvironment(Environment::DEFAULT);
		// environment scope starts
		conn = env->createConnection(user, pass, constr);

		// call method createStatement() to create a statement object
		Statement* stmt = conn->createStatement();
		stmt->setSQL("BEGIN SPPRJ_STORESELECT(:1, :2, :3, :4, :5, :6, :7, :8); END;");
		stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
		stmt->registerOutParam(2, Type::OCCINUMBER, sizeof(mallID));
		stmt->registerOutParam(3, Type::OCCISTRING, sizeof(storeName));
		stmt->registerOutParam(4, Type::OCCISTRING, sizeof(storeContactName));
		stmt->registerOutParam(5, Type::OCCINUMBER, sizeof(phone));
		stmt->registerOutParam(6, Type::OCCISTRING, sizeof(storeMail));
		stmt->registerOutParam(7, Type::OCCISTRING, sizeof(storeType));
		stmt->setString(8, storeID);

		stmt->executeUpdate();
		err = stmt->getInt(1);
		mallID = stmt->getNumber(2);
		storeName = stmt->getString(3);
		storeContactName = stmt->getString(4);
		phone = stmt->getNumber(5);
		storeMail = stmt->getString(6);
		storeType = stmt->getString(7);

		cout << endl << endl << "error number is:" << err << endl << endl;

		if (err > 0) {
			cout << endl << "Store details ========================" << endl
				<< "mall ID				: " << mallID << endl
				<< "store Name			: " << storeName << endl
				<< "store Contact Name		: " << storeContactName << endl
				<< "store Phone			: " << phone << endl
				<< "store Mail			: " << storeMail << endl
				<< "store Type			: " << storeType << endl
				<< endl;
		}
		else if(err <= 0 )
		{
			cout << endl << "ERROR : The entered StoreID : " << storeID << " does not exsists. " << endl;
		}
		conn->terminateStatement(stmt);

		env->terminateConnection(conn);
		cout << endl;
		// environment scope ends
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}
//==============================================================================================================



// these 4 procedures are done by Rahul Kumar ==================================================================
void insertNewProduct(string constr, string pass, string user, Environment* env, Connection* conn) {
	try {

		std::string prodID, storeID, prodDesc;
		int prodQuantity, prodCost, err = 0;

		cout << "Enter Product ID (Pxxx) : "; cin >> prodID;
		cout << "Enter Store ID (Mxxx-Sxxx) : "; cin >> storeID;
		cout << "Enter Product quantity : "; cin >> prodQuantity;
		cout << "Enter Product description : "; cin >> prodDesc;
		cout << "Enter Product cost : "; cin >> prodCost;

		env = Environment::createEnvironment(Environment::DEFAULT);
		// environment scope starts
		conn = env->createConnection(user, pass, constr);


		// call method createStatement() to create an statement object
		Statement* stmt = conn->createStatement();
		stmt->setSQL("BEGIN spINVENTORYINSERT(:1, :2, :3, :4, :5, :6); END;");
		stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
		stmt->setString(2, prodID);
		stmt->setString(3, storeID);
		stmt->setNumber(4, prodQuantity);
		stmt->setString(5, prodDesc);
		stmt->setNumber(6, prodCost);


		stmt->executeUpdate();
		err = stmt->getInt(1);

		if (err > 0) {
			cout << endl << err << " New product inserted Successfully !!" << endl;
		}
		else
		{
			cout << endl << "ERROR : The entered product ID may already exsists. " << endl;
		}

		conn->terminateStatement(stmt);

		env->terminateConnection(conn);
		cout << endl;
		// environment scope ends
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}
void deleteSales(string constr, string pass, string user, Environment* env, Connection* conn) {
	try {

		std::string salesID;
		int err = 0;

		cout << "Enter sales ID of varchar type(SL00x) that you wish to Delete: "; cin >> salesID;

		env = Environment::createEnvironment(Environment::DEFAULT);
		// environment scope starts
		conn = env->createConnection(user, pass, constr);

		// call method createStatement() to create an statement object
		Statement* stmt = conn->createStatement();
		stmt->setSQL("BEGIN SPSALESDELETE(:1, :2); END;");
		stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
		stmt->setString(2, salesID);

		stmt->executeUpdate();
		err = stmt->getInt(1);

		if (err > 0) {
			cout << endl << err << " store with sales ID : " << salesID << " Deleted Successfully !!" << endl;
		}
		else
		{
			cout << endl << "ERROR : The entered sales ID : " << salesID << " does not exsists. " << endl;
		}

		conn->terminateStatement(stmt);

		env->terminateConnection(conn);
		cout << endl;
		// environment scope ends
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}
void updateSales(string constr, string pass, string user, Environment* env, Connection* conn) {
	try {

		std::string salesID;
		int quantity, err = 0;

		cout << "Enter sales ID of varchar type(SLxxx) to pdate: "; cin >> salesID;
		cout << "Enter New sold quantity : "; cin >> quantity;

		env = Environment::createEnvironment(Environment::DEFAULT);
		// environment scope starts
		conn = env->createConnection(user, pass, constr);

		// call method createStatement() to create an statement object
		Statement* stmt = conn->createStatement();
		stmt->setSQL("BEGIN spSALESUPDATE(:1, :2, :3); END;");
		stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
		stmt->setString(2, salesID);
		stmt->setInt(3, quantity);

		stmt->executeUpdate();
		err = stmt->getInt(1);

		if (err > 0) {
			cout << endl << " sold quantity updated to " << quantity << " of sales ID : " << salesID << endl;
		}
		else
		{
			cout << endl << "ERROR : The entered salesID : " << salesID << " does not exsists. " << endl;
		}

		conn->terminateStatement(stmt);

		env->terminateConnection(conn);
		cout << endl;
		// environment scope ends
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}
void selectProduct(string constr, string pass, string user, Environment* env, Connection* conn) {
	try {
		int prodQuantity, prodCost, err = 0;
		std::string storeID, prodDesc, prodID;

		cout << "Enter Product ID to see detils: "; cin >> prodID;

		env = Environment::createEnvironment(Environment::DEFAULT);
		// environment scope starts
		conn = env->createConnection(user, pass, constr);

		// call method createStatement() to create a statement object
		Statement* stmt = conn->createStatement();
		stmt->setSQL("BEGIN spINVENTORYSELECT(:1, :2, :3, :4, :5, :6); END;");
		stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
		stmt->registerOutParam(2, Type::OCCISTRING, sizeof(storeID));
		stmt->registerOutParam(3, Type::OCCINUMBER, sizeof(prodQuantity));
		stmt->registerOutParam(4, Type::OCCISTRING, sizeof(prodDesc));
		stmt->registerOutParam(5, Type::OCCINUMBER, sizeof(prodCost));
		stmt->setString(6, prodID);

		stmt->executeUpdate();
		err = stmt->getInt(1);

		
		storeID = stmt->getString(2);
		prodQuantity = stmt->getNumber(3);
		prodDesc = stmt->getString(4);
		prodCost = stmt->getNumber(5);

		if (err > 0) {
			cout << endl << "Store details ========================" << endl
				<< "Product ID : " << prodID << endl
				<< "store ID : " << storeID << endl
				<< "Product	Quantity : " << prodQuantity << endl
				<< "Product Description	: " << prodDesc << endl
				<< "Product Cost : " << prodCost << endl
				<< endl;
		}
		if (err <= 0)
		{
			cout << endl << "ERROR : The entered StoreID : " << storeID << " does not exsists. " << endl;
		}

		conn->terminateStatement(stmt);

		env->terminateConnection(conn);
		cout << endl;
		// environment scope ends
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}
//==============================================================================================================



// these 4 procedures are doneby Harsh Lodhi ===================================================================
void createNewEmployee(string constr, string pass, string user, Environment* env, Connection* conn) {
	try {

		std::string empId, storeId, empDesignation, empFname, empLname;
		int mallId, empphone, err = 0;

		cout << "Enter Employee Id of varchar type (E00x) : "; cin >> empId;
		cout << "Enter Mall ID of int type (1-7) : "; cin >> mallId;
		cout << "Enter Store ID of varchar type (M000-S000) : "; cin >> storeId;
		cout << "Enter Employee Designation of varchar type : "; cin >> empDesignation;
		cout << "Enter Employee Phone having 10 digits (0000000000) : "; cin >> empphone;
		cout << "Enter the First name of the employee of Varchar Type: "; cin >> empFname;
		cout << "Enter the Last name of the employee of varchar type : "; cin >> empLname;

		env = Environment::createEnvironment(Environment::DEFAULT);
		// environment scope starts
		conn = env->createConnection(user, pass, constr);


		// call method createStatement() to create an statement object
		Statement* stmt = conn->createStatement();
		stmt->setSQL("BEGIN SPPRJ_EMPLOYEESINSERT(:1, :2, :3, :4, :5, :6, :7, :8); END;");
		stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
		stmt->setString(2, empId);
		stmt->setNumber(3, mallId);
		stmt->setString(4, storeId);
		stmt->setString(5, empDesignation);
		stmt->setString(6, empFname);
		stmt->setString(7, empLname);
		stmt->setNumber(8, empphone);

		stmt->executeUpdate();
		err = stmt->getInt(1);

		if (err > 0) {
			cout << endl << err << " Employee inserted Successfully !!" << endl;
		}
		else
		{
			cout << endl << "ERROR :Employee could not be inserted. The entered EmpID may already exsists. " << endl;
		}

		conn->terminateStatement(stmt);

		env->terminateConnection(conn);
		cout << endl;
		// environment scope ends
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}
void deleteEmployees(string constr, string pass, string user, Environment* env, Connection* conn) {
	try {

		std::string empId;
		int err = 0;

		cout << "Enter Employee ID of varchar type(E00x) that you wish to Delete: "; cin >> empId;

		env = Environment::createEnvironment(Environment::DEFAULT);
		// environment scope starts
		conn = env->createConnection(user, pass, constr);

		// call method createStatement() to create an statement object
		Statement* stmt = conn->createStatement();
		stmt->setSQL("BEGIN SPPRJ_EMPLOYEESDELETE(:1, :2); END;");
		stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
		stmt->setString(2, empId);

		stmt->executeUpdate();
		err = stmt->getInt(1);

		if (err > 0) {
			cout << endl << err << " Employee with EmpId : " << empId << " Deleted Successfully !!" << endl;
		}
		else if (err == -1)
		{
			cout << endl << "ERROR : The entered EmpId : " << empId << " does not exsists. " << endl;
		}
		else {
			cout << endl << "ERROR : EMployee could not be Deleted. " << endl;
		}

		conn->terminateStatement(stmt);

		env->terminateConnection(conn);
		cout << endl;
		// environment scope ends
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}
void updateEmployeeDesignation(string constr, string pass, string user, Environment* env, Connection* conn) {
	try {

		std::string empId, empDesignation;
		int err = 0;

		cout << "Enter  Employee ID of varchar type(E00x) whose Designation you wish to update: "; cin >> empId;
		cout << "Enter Designation of the employee : "; cin >> empDesignation;

		env = Environment::createEnvironment(Environment::DEFAULT);
		// environment scope starts
		conn = env->createConnection(user, pass, constr);

		// call method createStatement() to create an statement object
		Statement* stmt = conn->createStatement();
		stmt->setSQL("BEGIN SPPRJ_EMPLOYEESUPDATE(:1, :2, :3); END;");
		stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
		stmt->setString(2, empId);
		stmt->setString(3, empDesignation);

		stmt->executeUpdate();
		err = stmt->getInt(1);

		if (err > 0) {
			cout << endl << " Designation updated to " << empDesignation << " of Employee with EmpID : " << empId << endl;
		}
		else 
		{
			cout << endl << "ERROR : The entered EmpId : " << empId << " does not exsists. " << endl;
		}

		conn->terminateStatement(stmt);

		env->terminateConnection(conn);
		cout << endl;
		// environment scope ends
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}
void selectEmployees(string constr, string pass, string user, Environment* env, Connection* conn) {
	try {
		int mallID, empPhone, err = 0;
		std::string empId, storeId, empDesignation, empFirstname, EmpLastName;

		cout << "Enter Employee Id to see detils: "; cin >> empId;

		env = Environment::createEnvironment(Environment::DEFAULT);
		// environment scope starts
		conn = env->createConnection(user, pass, constr);

		// call method createStatement() to create a statement object
		Statement* stmt = conn->createStatement();
		stmt->setSQL("BEGIN SPPRJ_EMPLOYEESSELECT(:1, :2, :3, :4, :5, :6, :7, :8); END;");
		stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
		stmt->registerOutParam(2, Type::OCCINUMBER, sizeof(mallID));
		stmt->registerOutParam(3, Type::OCCISTRING, sizeof(storeId));
		stmt->registerOutParam(4, Type::OCCISTRING, sizeof(empDesignation));	
		stmt->registerOutParam(5, Type::OCCISTRING, sizeof(empFirstname));
		stmt->registerOutParam(6, Type::OCCISTRING, sizeof(EmpLastName));
		stmt->registerOutParam(7, Type::OCCINUMBER, sizeof(empPhone));
		stmt->setString(8, empId);

		stmt->executeUpdate();
		err = stmt->getInt(1);
		mallID = stmt->getNumber(2);
		storeId = stmt->getString(3);
		empDesignation = stmt->getString(4);
		empFirstname = stmt->getString(5);
		EmpLastName = stmt->getString(6);
		empPhone = stmt->getNumber(7);

		
		if (err >= 0) {
			cout << endl << "Employee details =========== " << endl
				<< "Mall ID				: " << mallID << endl
				<< "Store ID			: " << storeId << endl
				<< "Employee Designation: " << empDesignation << endl
				<< "Employee Phone		: " << empPhone << endl
				<< "Employee First name	: " << empFirstname << endl
				<< "Employee Last Name	: " << EmpLastName << endl
				<< endl;
		}
		else
		{
			cout << endl << "ERROR : The entered Employee ID: " << empId << " does not exsists. " << endl;
		}

		conn->terminateStatement(stmt);

		env->terminateConnection(conn);
		cout << endl;
		// environment scope ends
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}
//==============================================================================================================



// stored Procedures executing function ========================================================================

void storedProcedures(string constr, string pass, string user, Environment* env, Connection* conn) {
	int choice = 1;
	while (choice != 0)
	{
		cout << "Choose which procedure to execute ?" << endl
			<< "  0. Go Back" << endl 
			<< endl << "  Done by Jashanpreet ======================" << endl << endl
			<< "  1. CREATE a new store entry" << endl
			<< "  2. DELETE an existing store" << endl
			<< "  3. UPDATE the contactname of a store" << endl
			<< "  4. READ details of the Store" << endl
			<< endl << "  Done by Harsh Lodhi ======================" << endl << endl
			<< "  5. CREATE a new Employee" << endl
			<< "  6. Delete a existing employee" << endl
			<< "  7. Update the designation of the employee" << endl
			<< "  8. Display Employee Details" << endl
			<< endl << "  Done by Rahul Kumar ======================" << endl << endl
			<< "  9. INSERT a new Sales" << endl
			<< " 10. DELETE  an existing Sales" << endl
			<< " 11. UPDATE sold quantity of specific sales " << endl
			<< " 12. SELECT product Details" << endl
			<< "Enter choice : ";
		cin >> choice;
		cout << endl;
		switch (choice)
		{
		case 0:
			cout << "GOing Back" << endl << endl;
			break;
		case 1:
			createNewStore(constr, pass, user, env, conn);
			break;
		case 2:
			deleteStore(constr, pass, user, env, conn);
			break;
		case 3:
			updateStoreContactName(constr, pass, user, env, conn);
			break;
		case 4:
			selectStore(constr, pass, user, env, conn);
			break;
		case 5:
			createNewEmployee(constr, pass, user, env, conn);
			break;
		case 6:
			deleteEmployees(constr, pass, user, env, conn);
			break;
		case 7:
			updateEmployeeDesignation(constr, pass, user, env, conn);
			break;
		case 8:
			selectEmployees(constr, pass, user, env, conn);
			break;
		case 9:
			insertNewProduct(constr, pass, user, env, conn);
			break;	
		case 10:
			deleteSales(constr, pass, user, env, conn);
			break;	
		case 11:
			updateSales(constr, pass, user, env, conn);
			break;	
		case 12:
			selectProduct(constr, pass, user, env, conn);
			break;
		default:
			cout << "invalid Choice" << endl;
			break;

		}
	}
}

int main(void)
{   //OCCI Variables 
	Environment* env = nullptr;
	Connection* conn = nullptr;
	// define a reference to an object statement
	Statement* stmt1 = nullptr;
	// define a reference to an object resultset
	ResultSet* rs1 = nullptr;
	string constr = "myoracle12c.senecacollege.ca:1521/oracle12c";

	int stuDB = 1;
	string pass, user;
	cout << "Group Number - 1" << endl
		<< "JASHANPREET - 168854214" << endl
		<< "RAHUL KUMAR - 164072217" << endl
		<< "HARSH LODHI - 169677218" << endl
		<< "********* MALL ***************" << endl << endl;
	while (stuDB != 0)
	{
		cout << "Choose Student Database to connect: " << endl
			<< " 0. Exit" << endl
			<< " 1. JASHANPREET " << endl
			<< " 2. HARSH LODHI " << endl
			<< " 3. RAHUL KUMAR " << endl
			<< "Enter choice : ";
		cin >> stuDB;
		cout << endl;
		switch (stuDB)
		{
		case 0:
			cout << "exiting application" << endl;
			break;
		case 1:
			// JASHANPREET 
			pass = "12398986";
			user = "dbs311_231ncc10";
			break;
		case 2:
			// HARSH LODHI 
			pass = "97692309";
			user = "dbs311_231ncc16";
			break;
		case 3:
			// RAHUL KUMAR
			pass = "19452207";
			user = "dbs311_231ncc14";
			break;
		default:
			cout << "invalid Choice" << endl;
			break;
		}

		int select = 1;
		if (stuDB == 0)
			select = 0;

		while (select != 0)
		{
			cout << "Select what you want to do ?" << endl
				<< " 0. Go Back" << endl
				<< " 1. See Reports of the data " << endl
				<< " 2. Alter data of the stored tables " << endl
				<< "Enter choice : ";
			cin >> select;
			cout << endl;
			switch (select)
			{
			case 0:
				cout << "GOing Back" << endl << endl;
				break;
			case 1:
				dataReports(constr, pass, user, env, conn);
				break;
			case 2:
				storedProcedures(constr, pass, user, env, conn);
				break;
			default:
				break;
			}

		}
	}
	return 0;
}

*/