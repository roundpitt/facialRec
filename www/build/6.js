webpackJsonp([6],{

/***/ 310:
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "PreferencesLandingPageModule", function() { return PreferencesLandingPageModule; });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(0);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__ngx_translate_core__ = __webpack_require__(112);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_ionic_angular__ = __webpack_require__(111);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__preferencesLanding__ = __webpack_require__(322);
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};




var PreferencesLandingPageModule = (function () {
    function PreferencesLandingPageModule() {
    }
    return PreferencesLandingPageModule;
}());
PreferencesLandingPageModule = __decorate([
    Object(__WEBPACK_IMPORTED_MODULE_0__angular_core__["L" /* NgModule */])({
        declarations: [
            __WEBPACK_IMPORTED_MODULE_3__preferencesLanding__["a" /* PreferencesLandingPage */],
        ],
        imports: [
            __WEBPACK_IMPORTED_MODULE_2_ionic_angular__["g" /* IonicPageModule */].forChild(__WEBPACK_IMPORTED_MODULE_3__preferencesLanding__["a" /* PreferencesLandingPage */]),
            __WEBPACK_IMPORTED_MODULE_1__ngx_translate_core__["b" /* TranslateModule */].forChild()
        ],
        exports: [
            __WEBPACK_IMPORTED_MODULE_3__preferencesLanding__["a" /* PreferencesLandingPage */]
        ]
    })
], PreferencesLandingPageModule);

//# sourceMappingURL=preferenceslanding.module.js.map

/***/ }),

/***/ 322:
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "a", function() { return PreferencesLandingPage; });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(0);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_ionic_angular__ = __webpack_require__(111);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__pages__ = __webpack_require__(214);
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};




//import { MainPage } from '../pages';
var PreferencesLandingPage = (function () {
    function PreferencesLandingPage(navCtrl) {
        this.navCtrl = navCtrl;
        this.dateToday = new Date();
        this.locale = "en-us";
        this.month = this.dateToday.toLocaleString(this.locale, { month: "short" });
        this.day = this.dateToday.getDate();
        this.accounts = [
            { desc: 'DEBIT CARD PURCHASE', from: 'spend', to: 'Company A', type: 'Other' },
            { desc: 'DEBIT CARD PURCHASE', from: 'spend', to: 'Company B', type: 'Other' },
            { desc: 'DEBIT CARD PURCHASE', from: 'spend', to: 'Company C', type: 'Other' },
            { desc: 'DEBIT CARD PURCHASE', from: 'spend', to: 'Company D', type: 'Other' },
            { desc: 'DEBIT CARD PURCHASE', from: 'spend', to: 'Company E', type: 'Other' },
            { desc: 'DEBIT CARD PURCHASE', from: 'spend', to: 'Company F', type: 'Other' },
            { desc: 'DEBIT CARD PURCHASE', from: 'spend', to: 'Company G', type: 'Other' },
            { desc: 'DEBIT CARD PURCHASE', from: 'spend', to: 'Company H', type: 'Other' },
            { desc: 'DEBIT CARD PURCHASE', from: 'spend', to: 'Company I', type: 'Other' },
            { desc: 'DEBIT CARD PURCHASE', from: 'spend', to: 'Company J', type: 'Other' },
            { desc: 'DEBIT CARD PURCHASE', from: 'spend', to: 'Company K', type: 'Other' },
            { desc: 'DEBIT CARD PURCHASE', from: 'spend', to: 'Company L', type: 'Other' },
            { desc: 'DEBIT CARD PURCHASE', from: 'spend', to: 'Company M', type: 'Other' },
            { desc: 'DEBIT CARD PURCHASE', from: 'spend', to: 'Company N', type: 'Other' },
        ];
    }
    PreferencesLandingPage.prototype.ngAfterViewInit = function () {
    };
    PreferencesLandingPage.prototype.toQuickView = function () {
        this.navCtrl.push(__WEBPACK_IMPORTED_MODULE_2__pages__["d" /* QuickViewPage */]);
    };
    PreferencesLandingPage.prototype.toAuthentication = function () {
        this.navCtrl.push(__WEBPACK_IMPORTED_MODULE_2__pages__["a" /* AuthenticationPage */]);
    };
    return PreferencesLandingPage;
}());
PreferencesLandingPage = __decorate([
    Object(__WEBPACK_IMPORTED_MODULE_1_ionic_angular__["f" /* IonicPage */])(),
    Object(__WEBPACK_IMPORTED_MODULE_0__angular_core__["n" /* Component */])({
        selector: 'page-preferenceslanding',template:/*ion-inline-start:"C:\Users\SuperAdmin\facialRec\src\pages\preferencesLanding\preferenceslanding.html"*/'<ion-content>\n\n<ion-header hide-back-button="true">\n\n  <ion-navbar>\n\n    <ion-title style="    position: relative; top: 2px;" text-center>PREFERENCES</ion-title>\n\n      <ion-img style="    top: 17px;\n\n    position: absolute;\n\n    right: 5px;\n\n    width: 35px;\n\n    height: 40px;"  class="headerText" src="assets/img/calendarIcon.png"></ion-img>\n\n      <ion-img style="    top: 17px;\n\n    position: absolute;\n\n    right: 47px;\n\n    width: 35px;\n\n    height: 40px;"  class="headerText" src="assets/img/barIcon.png"></ion-img>\n\n  </ion-navbar>\n\n</ion-header>\n\n<div class="mainContent">\n\n  <ion-list>\n\n      <ion-item (click)="toAuthentication()" class="headerText">Authentication<div class="amountText">&gt;</div></ion-item>\n\n      <ion-item class="headerText">Money Bar Preview<div class="amountText">&gt;</div></ion-item>\n\n      <ion-item class="headerText">Punch The Pig<div class="amountText">&gt;</div></ion-item>\n\n      <ion-item class="headerText">Switch Accounts<div class="amountText">&gt;</div></ion-item>\n\n      <ion-item class="headerText">Zelle<sup>℠</sup> Preferences<div class="amountText">&gt;</div></ion-item>\n\n  </ion-list>\n\n</div>\n\n  <ion-footer id="footer">\n\n        <div class="row" text-center>\n\n          <div (click)="toQuickView()" class="column orange">\n\n            <ion-img width="10px" height="40px" style="position:relative; top:7px" src="assets/img/quickViewIcon.png"></ion-img>\n\n            Quick View\n\n          </div>\n\n          <div class="column">\n\n            <ion-img width="10px" height="40px" style="position:relative; top:7px" src="assets/img/depositIcon.png"></ion-img>\n\n            Deposit\n\n          </div>\n\n          <div class="column">\n\n            <ion-img width="10px" height="40px" style="position:relative; top:7px" src="assets/img/transferIcon.png"></ion-img>\n\n            Transfer\n\n          </div>\n\n          <div class="column"><button class="more" ion-button menuToggle>\n\n            <ion-img width="10px" height="40px" style="position:relative; top:7px" src="assets/img/moreIcon.png"></ion-img>\n\n            More\n\n          </button>\n\n          </div>\n\n        </div>\n\n</ion-footer>\n\n</ion-content>\n\n'/*ion-inline-end:"C:\Users\SuperAdmin\facialRec\src\pages\preferencesLanding\preferenceslanding.html"*/
    }),
    __metadata("design:paramtypes", [__WEBPACK_IMPORTED_MODULE_1_ionic_angular__["i" /* NavController */]])
], PreferencesLandingPage);

//# sourceMappingURL=preferencesLanding.js.map

/***/ })

});
//# sourceMappingURL=6.js.map