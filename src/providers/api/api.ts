import { HttpClient, HttpParams } from '@angular/common/http';
import { Injectable } from '@angular/core';
//import { RequestOptions } from '@angular/http';
//import { Headers } from '@angular/http';

/**
 * Api is a generic REST Api handler. Set your API url first.
 */
@Injectable()
export class Api {

  // env-5009919.njs.jelastic.vps-host.net       USE OFF PNC NETWORK                (QA dev)
  // http://PP74wc9wf2:8080/VisaX                USE ON PNC NETWORK                 (local dev)
  // IP can change
  // http://10.27.132.193:8080/VisaX               USE ON PNC NETWORK                 (local dev)

  url: string = 'http://10.29.140.42:8080/VisaX';

  constructor(public http: HttpClient) {
    
    
  }

  get(endpoint: string, params?: any, reqOpts?: any) {
    if (!reqOpts) {
      reqOpts = {
        params: new HttpParams()
      };
    }

    // Support easy query params for GET requests
    if (params) {
      reqOpts.params = new HttpParams();
      for (let k in params) {
        reqOpts.params.set(k, params[k]);
      }
    }

    return this.http.get(this.url + '/' + endpoint/*, this.options*/);
  }

  post(endpoint: string, body: any, reqOpts?: any) {


    return this.http.post(this.url + '/' + endpoint, body/*, this.options*/);
  }

  put(endpoint: string, body: any, reqOpts?: any) {
    return this.http.put(this.url + '/' + endpoint, body/*, this.options*/);
  }

  delete(endpoint: string, reqOpts?: any) {
    return this.http.delete(this.url + '/' + endpoint/*, this.options*/);
  }

  patch(endpoint: string, body: any, reqOpts?: any) {
    return this.http.put(this.url + '/' + endpoint, body/*, this.options*/);
  }
}
