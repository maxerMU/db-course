import { Component, Input, OnInit } from '@angular/core';
import { Event, NavigationEnd, Router } from '@angular/router';

@Component({
  selector: 'app-left-bar',
  templateUrl: './left-bar.component.html',
  styleUrls: ['./left-bar.component.less']
})
export class LeftBarComponent implements OnInit {
  label: Label = Label.STOCK;

  constructor(private router: Router) { 
    this.router.events.subscribe((event: Event) => {

      if (event instanceof NavigationEnd) {
        if (this.router.url == "/stock") {
          this.label = Label.STOCK;
        } else if (this.router.url == "/orders/new") {
          this.label = Label.STOCK;
        } else if (this.router.url == "/orders") {
          this.label = Label.ORDERS;
        } else if (this.router.url == "/workers") {
          this.label = Label.WORKERS;
        }
      }
  });

  }

  ngOnInit(): void {
  //   this.watchForUrl();
  }

  // watchForUrl(): void {
  //   if (this.router.url == "/orders") {
  //     this.label = Label.ORDERS;
  //   } else if (this.router.url == "/workers") {
  //     this.label = Label.WORKERS;
  //   }

  //   this.router.events.pipe(filter(event => event instanceof NavigationEnd)).subscribe((event: NavigationEnd) => {
  //     this.watchForUrl();
  //   });
  // }
}

export enum Label {
  STOCK,
  ORDERS,
  WORKERS
}
