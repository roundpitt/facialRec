webpackJsonp([0],{

/***/ 316:
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "ZelleLandingPageModule", function() { return ZelleLandingPageModule; });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(0);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__ngx_translate_core__ = __webpack_require__(112);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_ionic_angular__ = __webpack_require__(111);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__zelleLanding__ = __webpack_require__(328);
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};




var ZelleLandingPageModule = (function () {
    function ZelleLandingPageModule() {
    }
    return ZelleLandingPageModule;
}());
ZelleLandingPageModule = __decorate([
    Object(__WEBPACK_IMPORTED_MODULE_0__angular_core__["L" /* NgModule */])({
        declarations: [
            __WEBPACK_IMPORTED_MODULE_3__zelleLanding__["a" /* ZelleLandingPage */],
        ],
        imports: [
            __WEBPACK_IMPORTED_MODULE_2_ionic_angular__["g" /* IonicPageModule */].forChild(__WEBPACK_IMPORTED_MODULE_3__zelleLanding__["a" /* ZelleLandingPage */]),
            __WEBPACK_IMPORTED_MODULE_1__ngx_translate_core__["b" /* TranslateModule */].forChild()
        ],
        exports: [
            __WEBPACK_IMPORTED_MODULE_3__zelleLanding__["a" /* ZelleLandingPage */]
        ]
    })
], ZelleLandingPageModule);

//# sourceMappingURL=zellelanding.module.js.map

/***/ }),

/***/ 328:
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "a", function() { return ZelleLandingPage; });
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
var ZelleLandingPage = (function () {
    function ZelleLandingPage(navCtrl) {
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
    ZelleLandingPage.prototype.ngAfterViewInit = function () {
    };
    ZelleLandingPage.prototype.toQuickView = function () {
        this.navCtrl.push(__WEBPACK_IMPORTED_MODULE_2__pages__["d" /* QuickViewPage */]);
    };
    return ZelleLandingPage;
}());
ZelleLandingPage = __decorate([
    Object(__WEBPACK_IMPORTED_MODULE_1_ionic_angular__["f" /* IonicPage */])(),
    Object(__WEBPACK_IMPORTED_MODULE_0__angular_core__["n" /* Component */])({
        selector: 'page-zellelanding',template:/*ion-inline-start:"C:\Users\SuperAdmin\facialRec\src\pages\zelleLanding\zellelanding.html"*/'<ion-content>\n\n<ion-header hide-back-button="true">\n\n  <ion-navbar>\n\n    <ion-title style="    position: relative; top: 2px;" text-center>SEND MONEY WITH ZELLE™</ion-title>\n\n      <ion-img style="    top: 17px;\n\n    position: absolute;\n\n    right: 5px;\n\n    width: 35px;\n\n    height: 40px;"  class="headerText" src="assets/img/calendarIcon.png"></ion-img>\n\n      <ion-img style="    top: 17px;\n\n    position: absolute;\n\n    right: 47px;\n\n    width: 35px;\n\n    height: 40px;"  class="headerText" src="assets/img/barIcon.png"></ion-img>\n\n  </ion-navbar>\n\n</ion-header>\n\n<div class="mainContent">\n\n  <ion-list>\n\n    <ion-item>\n\n      <h2 class="headerText bold">FREE BALANCE</h2>\n\n      <h1 class="amountText green">$1,000.00</h1>\n\n    </ion-item>\n\n\n\n    <ion-item class="slim">\n\n      <h2 class="headerText bold">ACCOUNTS</h2>\n\n    </ion-item>\n\n\n\n    <ion-item class="medium image">\n\n      <ion-img width="10px" height="40px"  class="headerText" src="assets/img/spendDollar.png"></ion-img>\n\n      <h2 class="headerText orange">Spend</h2>\n\n      <h2 class="amountText">$1,000.00</h2>\n\n    </ion-item>\n\n\n\n    <ion-item class="medium image">\n\n      <ion-img width="10px" height="40px"  class="headerText" src="assets/img/reserveStar.png"></ion-img>\n\n      <h2 class="headerText blue">Reserve</h2>\n\n      <h2 class="amountText">$0.00</h2>\n\n    </ion-item>\n\n\n\n    <ion-item class="slim">\n\n      <p class="headerText blue">Show all accounts</p>\n\n    </ion-item>\n\n\n\n    <ion-item>\n\n      <h2 class="headerText bold">RECENT TRANSACTIONS</h2>\n\n    </ion-item>\n\n\n\n    <ion-item class="postedDate">\n\n      <h2 class="headerText" >{{(month?month:"Nov") + " " + (day?day:"15")}}</h2> <!-- sometimes date returns undefined. Needs to be bug proof for presentation. -->\n\n    </ion-item>\n\n\n\n    <ion-item *ngFor="let account of accounts">\n\n      <h3>{{account.desc}}</h3>\n\n    </ion-item>\n\n  </ion-list>\n\n</div>\n\n\n\n  <ion-footer id="footer">\n\n        <div class="row" text-center>\n\n          <div (click)="toQuickView()" class="column orange">\n\n            <ion-img width="10px" height="40px" style="position:relative; top:7px" src="assets/img/quickViewIcon.png"></ion-img>\n\n            Quick View\n\n          </div>\n\n          <div class="column">\n\n            <ion-img width="10px" height="40px" style="position:relative; top:7px" src="assets/img/depositIcon.png"></ion-img>\n\n            Deposit\n\n          </div>\n\n          <div class="column">\n\n            <ion-img width="10px" height="40px" style="position:relative; top:7px" src="assets/img/transferIcon.png"></ion-img>\n\n            Transfer\n\n          </div>\n\n          <div class="column"><button class="more" ion-button menuToggle>\n\n            <ion-img width="10px" height="40px" style="position:relative; top:7px" src="assets/img/moreIcon.png"></ion-img>\n\n            More\n\n          </button>\n\n          </div>\n\n        </div>\n\n</ion-footer>\n\n</ion-content>\n\n'/*ion-inline-end:"C:\Users\SuperAdmin\facialRec\src\pages\zelleLanding\zellelanding.html"*/
    }),
    __metadata("design:paramtypes", [__WEBPACK_IMPORTED_MODULE_1_ionic_angular__["i" /* NavController */]])
], ZelleLandingPage);

//# sourceMappingURL=zelleLanding.js.map

/***/ })

});
//# sourceMappingURL=0.js.map