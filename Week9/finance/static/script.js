"use strict";
import { getValidationCallback } from './js/validations.js';
// import { setLogoutSessionReminder } from '.js/logout-session-reminder.js';

// As part of 'personal touch' we added 2 new features on frontend side
//    1) Is a frontend side validation. It can disable submit buttons
//       if WITH_BLOCKING_VALIDATIONS = true. We kept false as default
//       in order to be able to test the backend side validations.
//    2) Anoter feature was the login reminder in frontend side.
//       That means that before user logout we save in localStorage it's
//       username so next time he joins the login session, it will be previous
//       fulfilled, remembering the last user logged in.

// Validations
const WITH_BLOCKING_VALIDATIONS = false; // Change it to true will disable submit button in case of validation errors

(() => {
    document.addEventListener('DOMContentLoaded', () => {
        const form = hasForm();
        if (!form) return;
        const validate = getValidationCallback(WITH_BLOCKING_VALIDATIONS);
        if (!validate) return;
        const test = addInputEvents(form, validate);
    });

    function hasForm() {
        const form = document.querySelector('form');
        if (form === null) return false;
        if (form.children.length === 0) return false;
        return form;
    }

    function addInputEvents(form, callback) {
        return [...document.querySelectorAll('input')]
            .forEach(input => {
                input.addEventListener('input', callback);
            });
    }
})();

// Storing username in localStorage after login if its not set or set for a different user
(() => {
    document.addEventListener('DOMContentLoaded', async () => {
        if (!hasJustLoggedIn()) return;
        const { localStorage } = window;
        if (!localStorage) {
            console.error("Error: document.localStorage not found. This browser version is unsupported");
            return;
        }
        const storedUsername = localStorage.getItem('lastUsernameUsed');
        const username = await getCurrentUsername();
        if (!username) {
            console.error("Error: username query is broke, the expected error also didn't occurred.");
            return;
        }
        if (username.error) {
            console.error(username.msg, username.error);
            return;
        }
        if (!storedUsername || storedUsername !== username) {
            localStorage.setItem('lastUsernameUsed', username);
        }
    });

    function hasJustLoggedIn() {
        const { pathname } = document.location ? document.location : window.location;
        const { referrer } = document;
        if (!(referrer && pathname)) return false;
        const splittedReferrerURL = referrer.split("/");
        const referrerPath = splittedReferrerURL[splittedReferrerURL.length - 1];
        return pathname === "/" && referrerPath === "login";
    }

    async function getCurrentUsername() {
        try {
            return await (
                await fetch('session-info').then(r => r.json())
            ).username;
        } catch(e) {
            return {
                msg: "USERNAME: Not able to get it!",
                error: e,
            }
        }
    }
})();
