webpackJsonp([6],{

/***/ 309:
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "PreferencesLandingPageModule", function() { return PreferencesLandingPageModule; });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(0);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__ngx_translate_core__ = __webpack_require__(112);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_ionic_angular__ = __webpack_require__(111);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__preferencesLanding__ = __webpack_require__(320);
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

/***/ 320:
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
        this.navCtrl.push(__WEBPACK_IMPORTED_MODULE_2__pages__["c" /* QuickViewPage */]);
    };
    return PreferencesLandingPage;
}());
PreferencesLandingPage = __decorate([
    Object(__WEBPACK_IMPORTED_MODULE_1_ionic_angular__["f" /* IonicPage */])(),
    Object(__WEBPACK_IMPORTED_MODULE_0__angular_core__["n" /* Component */])({
        selector: 'page-preferenceslanding',template:/*ion-inline-start:"C:\Users\round\Documents\facialRec\facialRec\src\pages\preferencesLanding\preferenceslanding.html"*/'<ion-content>\n<ion-header hide-back-button="true">\n  <ion-navbar>\n    <ion-title style="    position: relative; top: 2px;" text-center>PREFERENCES</ion-title>\n      <ion-img style="    top: 17px;\n    position: absolute;\n    right: 5px;\n    width: 35px;\n    height: 40px;"  class="headerText" src="assets/img/calendarIcon.png"></ion-img>\n      <ion-img style="    top: 17px;\n    position: absolute;\n    right: 47px;\n    width: 35px;\n    height: 40px;"  class="headerText" src="assets/img/barIcon.png"></ion-img>\n  </ion-navbar>\n</ion-header>\n<div class="mainContent">\n  <ion-list>\n    <ion-item>\n      <h2 class="headerText bold">FREE BALANCE</h2>\n      <h1 class="amountText green">$1,000.00</h1>\n    </ion-item>\n\n    <ion-item class="slim">\n      <h2 class="headerText bold">ACCOUNTS</h2>\n    </ion-item>\n\n    <ion-item class="medium image">\n      <ion-img width="10px" height="40px"  class="headerText" src="assets/img/spendDollar.png"></ion-img>\n      <h2 class="headerText orange">Spend</h2>\n      <h2 class="amountText">$1,000.00</h2>\n    </ion-item>\n\n    <ion-item class="medium image">\n      <ion-img width="10px" height="40px"  class="headerText" src="assets/img/reserveStar.png"></ion-img>\n      <h2 class="headerText blue">Reserve</h2>\n      <h2 class="amountText">$0.00</h2>\n    </ion-item>\n\n    <ion-item class="slim">\n      <p class="headerText blue">Show all accounts</p>\n    </ion-item>\n\n    <ion-item>\n      <h2 class="headerText bold">RECENT TRANSACTIONS</h2>\n    </ion-item>\n\n    <ion-item class="postedDate">\n      <h2 class="headerText" >{{(month?month:"Nov") + " " + (day?day:"15")}}</h2> <!-- sometimes date returns undefined. Needs to be bug proof for presentation. -->\n    </ion-item>\n\n    <ion-item *ngFor="let account of accounts">\n      <h3>{{account.desc}}</h3>\n    </ion-item>\n  </ion-list>\n</div>\n\n  <ion-footer id="footer">\n        <div class="row" text-center>\n          <div (click)="toQuickView()" class="column orange">\n            <ion-img width="10px" height="40px" style="position:relative; top:7px" src="assets/img/quickViewIcon.png"></ion-img>\n            Quick View\n          </div>\n          <div class="column">\n            <ion-img width="10px" height="40px" style="position:relative; top:7px" src="assets/img/depositIcon.png"></ion-img>\n            Deposit\n          </div>\n          <div class="column">\n            <ion-img width="10px" height="40px" style="position:relative; top:7px" src="assets/img/transferIcon.png"></ion-img>\n            Transfer\n          </div>\n          <div class="column"><button class="more" ion-button menuToggle>\n            <ion-img width="10px" height="40px" style="position:relative; top:7px" src="assets/img/moreIcon.png"></ion-img>\n            More\n          </button>\n          </div>\n        </div>\n</ion-footer>\n</ion-content>\n'/*ion-inline-end:"C:\Users\round\Documents\facialRec\facialRec\src\pages\preferencesLanding\preferenceslanding.html"*/
    }),
    __metadata("design:paramtypes", [__WEBPACK_IMPORTED_MODULE_1_ionic_angular__["i" /* NavController */]])
], PreferencesLandingPage);

//# sourceMappingURL=preferencesLanding.js.map

/***/ })

});
//# sourceMappingURL=6.js.map