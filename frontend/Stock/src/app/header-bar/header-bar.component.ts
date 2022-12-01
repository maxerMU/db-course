import { Component, OnInit } from '@angular/core';
import { AuthService } from '../auth.service';
import { Worker } from '../worker';

@Component({
  selector: 'app-header-bar',
  templateUrl: './header-bar.component.html',
  styleUrls: ['./header-bar.component.less']
})
export class HeaderBarComponent implements OnInit {
  me: Worker = {
    id: 1,
    name: '',
    surname: '',
    privilege: 0,
    birthdate: ''
  };

  constructor(private authService: AuthService) { }

  ngOnInit(): void {
    this.getMe();
  }

  getMe(): void {
    this.authService.getMe().subscribe(res => this.me = res);
  }

}
