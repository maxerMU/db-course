import { Component, OnInit } from '@angular/core';
import { AuthService } from '../auth.service';
import { Router } from '@angular/router';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.less']
})
export class LoginComponent implements OnInit {
  username = '';
  password = '';

  constructor(private auth: AuthService,
              private router: Router) { }

  ngOnInit(): void {
  }

  onSelect() {
    this.auth.login(this.username, this.password).subscribe(res => {
      localStorage.setItem('token', res!.access_token);
      console.log('token ', res!.access_token);
      this.router.navigateByUrl('/');
    })

  }
}
