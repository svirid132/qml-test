.pragma library
.import Singelton 1.0 as S
.import View 1.0 as V

const EmployeePuller = {
    create: function() {
        return Object.assign(this)
    },
    target: S.Employee,
    source: undefined,
    pull: function() {
        try {
            const target = this.target
            const source = this.source
            target.mId = source.mId
            target.firstName = source.firstName
            target.lastName = source.lastName
            const additioanlTarget = target.additionalEmp
            const additioanlSource = source.additionalEmp
            additioanlTarget.mId = additioanlSource.mId
            additioanlTarget.address = additioanlSource.address
            additioanlTarget.phone = additioanlSource.phone
            additioanlTarget.maritalStatus = additioanlSource.maritalStatus
            additioanlTarget.countryCodes = additioanlSource.countryCodes
        } catch(error) {
            console.exception('ошибка puller', error)
        }
    }
}
