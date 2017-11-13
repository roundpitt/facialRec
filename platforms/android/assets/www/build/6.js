webpackJsonp([6],{

/***/ 307:
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "LoginPageModule", function() { return LoginPageModule; });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(0);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__ngx_translate_core__ = __webpack_require__(112);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_ionic_angular__ = __webpack_require__(111);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__login__ = __webpack_require__(316);
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};




var LoginPageModule = (function () {
    function LoginPageModule() {
    }
    return LoginPageModule;
}());
LoginPageModule = __decorate([
    Object(__WEBPACK_IMPORTED_MODULE_0__angular_core__["L" /* NgModule */])({
        declarations: [
            __WEBPACK_IMPORTED_MODULE_3__login__["a" /* LoginPage */],
        ],
        imports: [
            __WEBPACK_IMPORTED_MODULE_2_ionic_angular__["f" /* IonicPageModule */].forChild(__WEBPACK_IMPORTED_MODULE_3__login__["a" /* LoginPage */]),
            __WEBPACK_IMPORTED_MODULE_1__ngx_translate_core__["b" /* TranslateModule */].forChild()
        ],
        exports: [
            __WEBPACK_IMPORTED_MODULE_3__login__["a" /* LoginPage */]
        ]
    })
], LoginPageModule);

//# sourceMappingURL=login.module.js.map

/***/ }),

/***/ 316:
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "a", function() { return LoginPage; });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(0);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__ngx_translate_core__ = __webpack_require__(112);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_ionic_angular__ = __webpack_require__(111);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__pages__ = __webpack_require__(214);
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};




//import { User } from '../../providers/providers';

var LoginPage = (function () {
    function LoginPage(navCtrl, toastCtrl, translateService, events) {
        var _this = this;
        this.navCtrl = navCtrl;
        this.toastCtrl = toastCtrl;
        this.translateService = translateService;
        this.events = events;
        // The account fields for the login form.
        // If you're using the username field with or without email, make
        // sure to add it to the type
        this.account = {
            username: '',
            password: ''
        };
        this.checkSubmit = function () {
            if (this.account.username != "" &&
                this.account.username != null &&
                this.account.password != "" &&
                this.account.password != null) {
                document.getElementById("loginBtn").disabled = false;
            }
            else {
                document.getElementById("loginBtn").disabled = true;
            }
        };
        this.floatLabel = function (id) {
            document.getElementById(id).style.transition = "all .5s ease";
            document.getElementById(id).style.transform = "translateY(-30px)";
            document.getElementById(id).style.animation = "sixPhasesFadeIn .5s";
            document.getElementById(id).style.opacity = "1";
        };
        this.blurLabel = function (id) {
            console.log(id);
            if (id == 'userIdLabel') {
                if (this.account.username != "" &&
                    this.account.username != null) {
                }
                else {
                    document.getElementById(id).style.transition = "all .5s ease";
                    document.getElementById(id).style.transform = "translateY(0)";
                    document.getElementById(id).style.animation = "sixPhasesFadeOut .5s";
                    document.getElementById(id).style.opacity = "0";
                }
            }
            else {
                if (this.account.password != "" &&
                    this.account.password != null) {
                }
                else {
                    document.getElementById(id).style.transition = "all .5s ease";
                    document.getElementById(id).style.transform = "translateY(0)";
                    document.getElementById(id).style.animation = "sixPhasesFadeOut .5s";
                    document.getElementById(id).style.opacity = "0";
                }
            }
        };
        this.translateService.get('LOGIN_ERROR').subscribe(function (value) {
            _this.loginErrorString = value;
        });
        events.subscribe('native.keyboardshow', function (e) {
            document.getElementById("footer").style.display = "none";
        });
        events.subscribe('native.keyboardhide', function (e) {
            document.getElementById("footer").style.display = "block";
        });
    }
    LoginPage.prototype.ngAfterViewInit = function () {
    };
    // open the selfie capture page
    LoginPage.prototype.doLogin = function () {
        this.navCtrl.push(__WEBPACK_IMPORTED_MODULE_3__pages__["c" /* QuickViewPage */]);
    };
    return LoginPage;
}());
LoginPage = __decorate([
    Object(__WEBPACK_IMPORTED_MODULE_0__angular_core__["n" /* Component */])({
        selector: 'page-login',template:/*ion-inline-start:"C:\Users\round\Documents\facialRec\facialRec\src\pages\login\login.html"*/'<ion-content>\n  <ion-img width="90%" height="103px" src="assets/img/login-logo.png"></ion-img>\n\n    <ion-card class="userIDCard">\n      <ion-label class="floatLabel" id="userIdLabel" >User ID</ion-label>\n      <ion-input placeholder="User ID" type="text" (keyup)="checkSubmit()" (ionBlur)="blurLabel(\'userIdLabel\')" (ionFocus)="floatLabel(\'userIdLabel\')"  [(ngModel)]="account.username" id="username" name="username"></ion-input>\n    </ion-card>\n\n    <ion-card>\n      <ion-label class="floatLabel" id="passwordLabel" >Password</ion-label>\n      <ion-input id="passwordInput" placeholder="Password" (keyup)="checkSubmit()" type="password" (ionBlur)="blurLabel(\'passwordLabel\')" (ionFocus)="floatLabel(\'passwordLabel\')"  [(ngModel)]="account.password" name="password"></ion-input>\n    </ion-card>\n\n    <div style="color:white; width:140px; margin:auto;">\n      Remember Me <ion-checkbox [(ngModel)]="thing" height="14px" width="14px"></ion-checkbox>\n    </div>\n\n<ion-card style="margin-top:20px">\n    <button id="loginBtn" (click)="doLogin()" ion-button disabled>Sign On</button>\n  </ion-card>\n\n  <div style="color:white; width:140px; margin:auto; margin-top:25px;">\n    Forgot Password?\n  </div>\n\n<ion-footer id="footer">\n        <div class="row" text-center>\n          <div class="column">\n            <ion-img width="10px" height="40px" src="assets/img/location.png"></ion-img>\n            Locate\n          </div>\n          <div class="column">\n            <ion-img width="40px" height="40px" style="position:relative; top:7px;" src="assets/img/moneybar.png"></ion-img>\n            View\n          </div>\n          <div class="column">\n            <ion-img width="10px" height="40px" style="position:relative; top:7px" src="assets/img/questionmark.png"></ion-img>\n            Help\n          </div>\n        </div>\n</ion-footer>\n\n</ion-content>\n'/*ion-inline-end:"C:\Users\round\Documents\facialRec\facialRec\src\pages\login\login.html"*/
    }),
    __metadata("design:paramtypes", [__WEBPACK_IMPORTED_MODULE_2_ionic_angular__["h" /* NavController */],
        __WEBPACK_IMPORTED_MODULE_2_ionic_angular__["k" /* ToastController */],
        __WEBPACK_IMPORTED_MODULE_1__ngx_translate_core__["c" /* TranslateService */], __WEBPACK_IMPORTED_MODULE_2_ionic_angular__["b" /* Events */]])
], LoginPage);

//# sourceMappingURL=login.js.map

/***/ })

});
//# sourceMappingURL=6.js.map