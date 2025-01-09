export const getValidationCallback = (disableSubmit) => {
    const validation = {
        isSubmitDisabled: () => disableSubmit,
    }
    const buy = validateBuy.bind(validation);
    const quote = buy; // separating in case validations change in possible future versions, for now they're the same
    const sell = validateSell.bind(validation);
    const deposit = validateDeposit.bind(validation);
    const login = validateLogin.bind(validation);
    const register = validateRegister.bind(validation);
    const change_password = validatePasswordChange.bind(validation);

    const { pathname } = document.location ? document.location : window.location;

    switch(pathname) {
        case "/quote":
            return quote;
        case "/buy":
            return buy;
        case "/sell":
            return sell;
        case "/add-cash":
            return deposit;
        case "/login":
            return login;
        case "/register":
            return register;
        case "/change-password":
            return change_password;
        default:
            return false;
    };
}


function validateBuy(event) {
    const submit = this.isSubmitDisabled() ? document.querySelector('[type="submit"]') : { disabled: false };
    const t = event.target;

    switch(t.name) {
        case 'symbol':
            if (t.value.length < 3) {
                removeValidationMessages(t);
                renderValidationMessage(t, "Stock Symbol code has at least 3 characters!");
                submit.disabled = this.isSubmitDisabled();
                break;
            }
            submit.disabled = false;
            removeValidationMessages(t);
            break;
        case 'shares':
            if (Number(t.value) <= 0) {
                removeValidationMessages(t);
                renderValidationMessage(t, "Shares have to be a greater than 0!");
                submit.disabled = this.isSubmitDisabled();
                break;
            }
            submit.disabled = false;
            removeValidationMessages(t);
            break;
    }
}

function validateSell(event) {
    const submit = this.isSubmitDisabled() ? document.querySelector('[type="submit"]') : { disabled: false };
    const t = event.target;
        const s = {
        margin: "2px 0 -17px 10.5vw",
        fontSize: "7.5pt"
    }

    switch(t.name) {
        case 'shares':
            if (Number(t.value) <= 0) {
                removeValidationMessages(t);
                renderValidationMessage(t, "Shares have to be a positive number!", s);
                submit.disabled = this.isSubmitDisabled();
                break;
            }
            submit.disabled = false;
            removeValidationMessages(t);
            break;
    }
}

function validateDeposit(event) {
    const submit = this.isSubmitDisabled() ? document.querySelector('[type="submit"]') : { disabled: false };
    const t = event.target;

    switch(t.name) {
        case 'cash':
            if (Number(t.value) <= 0) {
                removeValidationMessages(t);
                renderValidationMessage(t, "Cash has to be a positive number!");
                submit.disabled = this.isSubmitDisabled();
                break;
            }
            submit.disabled = false;
            removeValidationMessages(t);
            break;
    }
}


function validateLogin(event) {
    const submit = this.isSubmitDisabled() ? document.querySelector('[type="submit"]') : { disabled: false };
    const t = event.target;
    const s = {
        margin: "-21.5px 0 -7.5px",
        fontSize: "7.5pt"
    }

    switch(t.name) {
        case 'username':
            if (t.value.length < 3) {
                removeValidationMessages(t.parentElement);
                renderValidationMessage(t.parentElement, "Name must have more than 3 characters", s);
                submit.disabled = this.isSubmitDisabled();
                break
            }
            submit.disabled = false;
            removeValidationMessages(t.parentElement);
            break;
        case 'password':
            if (t.value.length < 8) {
                removeValidationMessages(t.parentElement);
                renderValidationMessage(t.parentElement, "Passwords must have at least 8 characters", s);
                submit.disabled = this.isSubmitDisabled();
                break
            }
            submit.disabled = false;
            removeValidationMessages(t.parentElement);
            break;
    }
}

function validateRegister(event) {
    const submit = this.isSubmitDisabled() ? document.querySelector('[type="submit"]') : { disabled: false };
    const t = event.target;
    const pswdInputs = document.querySelectorAll('[type="password"]');
    switch(t.name) {
        case 'username':
            if (t.value.length < 3) {
                removeValidationMessages(t);
                renderValidationMessage(t, "Name must have more than 3 characters");
                submit.disabled = this.isSubmitDisabled();
                break
            }
            submit.disabled = false;
            removeValidationMessages(t);
            break;
        case 'password':
            if (t.value.length < 8) {
                removeValidationMessages(t);
                renderValidationMessage(t, "Passwords must have at least 7 characters");
                submit.disabled = this.isSubmitDisabled();
                break;
            }
            else if (t.value !== pswdInputs[1].value) {
                pswdInputs.forEach(pswdInput => removeValidationMessages(pswdInput));
                renderValidationMessage(pswdInputs[1], "Passwords are not matching!");
                submit.disabled = this.isSubmitDisabled();
                break
            }
            submit.disabled = false;
            pswdInputs.forEach(pswdInput => removeValidationMessages(pswdInput));
            break;
        case 'confirmation':
            if (t.value !== pswdInputs[0].value) {
                removeValidationMessages(t);
                renderValidationMessage(t, "Passwords are not matching!");
                submit.disabled = this.isSubmitDisabled();
                break
            }
            submit.disabled = false;
            removeValidationMessages(t);
            break;
    }
}


function validatePasswordChange(event) {
    const submit = this.isSubmitDisabled() ? document.querySelector('[type="submit"]') : { disabled: false };
    const t = event.target;
    const pswdInputs = document.querySelectorAll('[type="password"]');
    switch(t.name) {
        case 'username':
            if (t.value.length < 3) {
                removeValidationMessages(t);
                renderValidationMessage(t, "Name must have more than 3 characters");
                submit.disabled = this.isSubmitDisabled();
                break
            }
            submit.disabled = false;
            removeValidationMessages(t);
            break;
        case 'password':
            if (t.value.length < 8) {
                removeValidationMessages(t);
                renderValidationMessage(t, "Passwords must have at least 7 characters");
                submit.disabled = this.isSubmitDisabled();
                break;
            }
            else if (t.value !== pswdInputs[1].value) {
                pswdInputs.forEach(pswdInput => removeValidationMessages(pswdInput));
                renderValidationMessage(pswdInputs[1], "Passwords are not matching!");
                submit.disabled = this.isSubmitDisabled();
                break
            }
            submit.disabled = false;
            pswdInputs.forEach(pswdInput => removeValidationMessages(pswdInput));
            break;
        case 'confirmation':
            if (t.value !== pswdInputs[0].value) {
                removeValidationMessages(t);
                renderValidationMessage(t, "Passwords are not matching!");
                submit.disabled = this.isSubmitDisabled();
                break
            }
            submit.disabled = false;
            removeValidationMessages(t);
            break;
        case 'new_password':
            if (t.value.length < 8) {
                removeValidationMessages(t);
                renderValidationMessage(t, "Passwords must have at least 7 characters");
                submit.disabled = this.isSubmitDisabled();
                break;
            }
            submit.disabled = false;
            removeValidationMessages(t);
            break;
    }
}

function renderValidationMessage(el, message, style = {margin: "-14.5px", fontSize: "7.5pt" }) {
    if (el.nexElementSibling && el.nextElementSibling.tagName === 'P') return;
    const p = document.createElement('p');
    p.innerText = message;
    p.style.fontSize = style.fontSize;
    p.style.fontWeight = "bolder";
    p.style.margin = style.margin;
    p.style.color = "red";
    el.insertAdjacentElement('afterend', p);
}

function removeValidationMessages(el) {
    const nextSib = el.nextElementSibling;
    if (nextSib && nextSib.tagName === 'P') nextSib.remove();
}
