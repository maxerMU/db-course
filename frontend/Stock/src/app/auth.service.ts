import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { AuthInfo } from './auth-info';
import { Worker, WorkerSignup } from './worker';
import { Observable } from 'rxjs';
import { map } from 'rxjs/operators'

@Injectable({
  providedIn: 'root'
})
export class AuthService {

  constructor(private http: HttpClient) { }

  login(username: string, password: string) {
    return this.http.post<AuthInfo>(this.authUrl, {username, password});
  }

  signup(workerSignup: WorkerSignup) {
    return this.http.post(this.workersUrl, workerSignup)
  }

  getMe(): Observable<Worker> {
    return this.http.get<Worker>(this.getMeUrl);
  }

  getWorker(workerId: number): Observable<Worker> {
    return this.http.get<Worker>(this.workersUrl + '/' + workerId.toString());
  }

  getWorkers(): Observable<Worker[]> {
    return this.http.get<Workers>(this.workersUrl).pipe(
      map((workers: Workers) => workers.workers)
    )
  }

  updatePrivilege(worker_id: number, newPrivilege: number) {
    return this.http.patch(this.workersUrl + '/' + worker_id.toString() + '/' + 'privilege', {privilege_level: newPrivilege});
  }

  private authUrl = 'https://localhost/api/v1/auth/login'
  private getMeUrl = 'https://localhost/api/v1/workers/me'
  private workersUrl = 'https://localhost/api/v1/workers'
}

interface Workers {
  workers: Worker[];
}