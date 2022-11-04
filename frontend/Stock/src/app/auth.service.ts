import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { AuthInfo } from './auth-info';
import { Worker } from './worker';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class AuthService {

  constructor(private http: HttpClient) { }

  login(username: string, password: string) {
    return this.http.post<AuthInfo>(this.authUrl, {username, password});
  }

  getMe(): Observable<Worker> {
    return this.http.get<Worker>(this.getMeUrl);
  }

  getWorker(workerId: number): Observable<Worker> {
    return this.http.get<Worker>(this.workersUrl + '/' + workerId.toString());
  }

  private authUrl = 'https://localhost/api/v1/auth/login'
  private getMeUrl = 'https://localhost/api/v1/workers/me'
  private workersUrl = 'https://localhost/api/v1/workers'
}
