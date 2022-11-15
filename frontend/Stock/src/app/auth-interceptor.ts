import { Injectable } from '@angular/core';
import { HttpRequest, HttpHandler, HttpEvent, HttpInterceptor, HttpErrorResponse } from '@angular/common/http';
import { Observable, timer } from 'rxjs';
import {concatMap, delay, retry, tap} from 'rxjs/operators';
import {Router} from '@angular/router';

@Injectable()
export class AuthInterceptor implements HttpInterceptor {

    constructor(private router: Router) {}

    intercept(req: HttpRequest<any>,
              next: HttpHandler): Observable<HttpEvent<any>> {

        const idToken = localStorage.getItem("token");

        if (idToken) {
            req = req.clone({
                headers: req.headers.set("Autharization", idToken)
            });

        }
        return next.handle(req).pipe( tap(() => {},
          (err: any) => {
          if (err instanceof HttpErrorResponse) {
            if (err.status !== 401) {
             return;
            }
            this.router.navigateByUrl('/login');
          }
        }),
        retry(3));
    }
}