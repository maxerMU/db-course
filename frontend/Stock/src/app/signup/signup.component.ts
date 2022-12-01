import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { AuthService } from '../auth.service';
import { WorkerSignup } from '../worker';

@Component({
  selector: 'app-signup',
  templateUrl: './signup.component.html',
  styleUrls: ['./signup.component.less']
})
export class SignupComponent implements OnInit {
  worker: WorkerSignup = {
    name: '',
    surname: '',
    birthdate: '',
    username: '',
    password: ''
  }

  constructor(private authService: AuthService,
              private router: Router) { }

  ngOnInit(): void {
  }

  onSelect() {
    this.authService.signup(this.worker).subscribe();
    this.router.navigateByUrl('/login')
  }

}
