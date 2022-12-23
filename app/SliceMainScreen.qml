pragma Singleton

import QtQuick 2.0
import Model 1.0
import Controller 1.0

QtObject {
    property Employee employee: Employee {
        id: emp
        additionalEmp: AdditionalEmp {
            id: addEmp
        }
    }

    property EmployeeController empController: EmployeeController {
        target: emp
    }

    property var setEmployee: function(payload) {
        emp.mId = payload.emp_id
        emp.firstName = payload.emp_firstName
        emp.lastName = payload.emp_lastName
        addEmp.mId = payload.additional_id
    }

    property var getAdditionalEmployee: function() {
        empController.getAdditionalEmployee()
    }
}
