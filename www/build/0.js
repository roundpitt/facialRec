webpackJsonp([0],{

/***/ 320:
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "ZelleOptionsPageModule", function() { return ZelleOptionsPageModule; });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(0);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__ngx_translate_core__ = __webpack_require__(112);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_ionic_angular__ = __webpack_require__(111);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__zelleOptions__ = __webpack_require__(336);
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};




var ZelleOptionsPageModule = (function () {
    function ZelleOptionsPageModule() {
    }
    return ZelleOptionsPageModule;
}());
ZelleOptionsPageModule = __decorate([
    Object(__WEBPACK_IMPORTED_MODULE_0__angular_core__["L" /* NgModule */])({
        declarations: [
            __WEBPACK_IMPORTED_MODULE_3__zelleOptions__["a" /* ZelleOptionsPage */],
        ],
        imports: [
            __WEBPACK_IMPORTED_MODULE_2_ionic_angular__["g" /* IonicPageModule */].forChild(__WEBPACK_IMPORTED_MODULE_3__zelleOptions__["a" /* ZelleOptionsPage */]),
            __WEBPACK_IMPORTED_MODULE_1__ngx_translate_core__["b" /* TranslateModule */].forChild()
        ],
        exports: [
            __WEBPACK_IMPORTED_MODULE_3__zelleOptions__["a" /* ZelleOptionsPage */]
        ]
    })
], ZelleOptionsPageModule);

//# sourceMappingURL=zelleOptions.module.js.map

/***/ }),

/***/ 336:
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "a", function() { return ZelleOptionsPage; });
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
var ZelleOptionsPage = (function () {
    function ZelleOptionsPage(navCtrl) {
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
    ZelleOptionsPage.prototype.ngAfterViewInit = function () {
    };
    ZelleOptionsPage.prototype.toQuickView = function () {
        this.navCtrl.push(__WEBPACK_IMPORTED_MODULE_2__pages__["f" /* QuickViewPage */]);
    };
    return ZelleOptionsPage;
}());
ZelleOptionsPage = __decorate([
    Object(__WEBPACK_IMPORTED_MODULE_0__angular_core__["n" /* Component */])({
        selector: 'page-zelleOptions',template:/*ion-inline-start:"C:\Users\SuperAdmin\facialRec\src\pages\zelleOptions\zelleOptions.html"*/'<ion-content>\n\n<ion-header hide-back-button="true">\n\n  <ion-navbar>\n\n    <ion-title style="    position: relative; top: 2px;" text-center>ZELLE<sup>℠</sup> OPTIONS</ion-title>\n\n      <ion-img style="    top: 17px;\n\n    position: absolute;\n\n    right: 5px;\n\n    width: 35px;\n\n    height: 40px;"  class="headerText" src="assets/img/calendarIcon.png"></ion-img>\n\n      <ion-img style="    top: 17px;\n\n    position: absolute;\n\n    right: 47px;\n\n    width: 35px;\n\n    height: 40px;"  class="headerText" src="assets/img/barIcon.png"></ion-img>\n\n  </ion-navbar>\n\n</ion-header>\n\n<div class="mainContent">\n\n  <ion-list>\n\n      <ion-item class="headerText">Threshold<div class="amountText">$<input type="number" min="0.00" step="0.01" max="10" value="0.00" onClick="this.select();"></div></ion-item>\n\n      <ion-item class="headerText">Authentication Type<div class="amountText"><select>\n\n          <option value="none">None</option>\n\n          <option value="password" selected="selected">Password</option>\n\n          <option value="pin">PIN</option>\n\n          <option value="pattern">Pattern</option>\n\n          <option value="face">Face ID</option>\n\n          <option value="touch">Fingerprint ID</option>\n\n          <option value="voice">Voice ID</option>\n\n        </select></div></ion-item>\n\n      <ion-item class="headerText">Geo-Lock<div class="amountText"><select>\n\n  <option value="AL">Alabama</option>\n\n  <option value="AK">Alaska</option>\n\n  <option value="AZ">Arizona</option>\n\n  <option value="AR">Arkansas</option>\n\n  <option value="CA">California</option>\n\n  <option value="CO">Colorado</option>\n\n  <option value="CT">Connecticut</option>\n\n  <option value="DE">Delaware</option>\n\n  <option value="DC">District Of Columbia</option>\n\n  <option value="FL">Florida</option>\n\n  <option value="GA">Georgia</option>\n\n  <option value="HI">Hawaii</option>\n\n  <option value="ID">Idaho</option>\n\n  <option value="IL">Illinois</option>\n\n  <option value="IN">Indiana</option>\n\n  <option value="IA">Iowa</option>\n\n  <option value="KS">Kansas</option>\n\n  <option value="KY">Kentucky</option>\n\n  <option value="LA">Louisiana</option>\n\n  <option value="ME">Maine</option>\n\n  <option value="MD">Maryland</option>\n\n  <option value="MA">Massachusetts</option>\n\n  <option value="MI">Michigan</option>\n\n  <option value="MN">Minnesota</option>\n\n  <option value="MS">Mississippi</option>\n\n  <option value="MO">Missouri</option>\n\n  <option value="MT">Montana</option>\n\n  <option value="NE">Nebraska</option>\n\n  <option value="NV">Nevada</option>\n\n  <option value="NH">New Hampshire</option>\n\n  <option value="NJ">New Jersey</option>\n\n  <option value="NM">New Mexico</option>\n\n  <option value="NY">New York</option>\n\n  <option value="NC">North Carolina</option>\n\n  <option value="ND">North Dakota</option>\n\n  <option value="OH">Ohio</option>\n\n  <option value="OK">Oklahoma</option>\n\n  <option value="OR">Oregon</option>\n\n  <option value="PA" selected="selected">Pennsylvania</option>\n\n  <option value="RI">Rhode Island</option>\n\n  <option value="SC">South Carolina</option>\n\n  <option value="SD">South Dakota</option>\n\n  <option value="TN">Tennessee</option>\n\n  <option value="TX">Texas</option>\n\n  <option value="UT">Utah</option>\n\n  <option value="VT">Vermont</option>\n\n  <option value="VA">Virginia</option>\n\n  <option value="WA">Washington</option>\n\n  <option value="WV">West Virginia</option>\n\n  <option value="WI">Wisconsin</option>\n\n  <option value="WY">Wyoming</option>\n\n</select>       </div></ion-item>\n\n    </ion-list>\n\n</div>\n\n  <ion-footer id="footer">\n\n        <div class="row" text-center>\n\n          <div (click)="toQuickView()" class="column orange">\n\n            <ion-img width="10px" height="40px" style="position:relative; top:7px" src="assets/img/quickViewIcon.png"></ion-img>\n\n            Quick View\n\n          </div>\n\n          <div class="column">\n\n            <ion-img width="10px" height="40px" style="position:relative; top:7px" src="assets/img/depositIcon.png"></ion-img>\n\n            Deposit\n\n          </div>\n\n          <div class="column">\n\n            <ion-img width="10px" height="40px" style="position:relative; top:7px" src="assets/img/transferIcon.png"></ion-img>\n\n            Transfer\n\n          </div>\n\n          <div class="column"><button class="more" ion-button menuToggle>\n\n            <ion-img width="10px" height="40px" style="position:relative; top:7px" src="assets/img/moreIcon.png"></ion-img>\n\n            More\n\n          </button>\n\n          </div>\n\n        </div>\n\n</ion-footer>\n\n</ion-content>\n\n'/*ion-inline-end:"C:\Users\SuperAdmin\facialRec\src\pages\zelleOptions\zelleOptions.html"*/
    }),
    __metadata("design:paramtypes", [__WEBPACK_IMPORTED_MODULE_1_ionic_angular__["i" /* NavController */]])
], ZelleOptionsPage);

//# sourceMappingURL=zelleOptions.js.map

/***/ })

});
//# sourceMappingURL=0.js.map