import { Component, Input, OnInit } from '@angular/core';

@Component({
  selector: 'app-left-bar',
  templateUrl: './left-bar.component.html',
  styleUrls: ['./left-bar.component.less']
})
export class LeftBarComponent implements OnInit {
  @Input() label: Label = Label.STOCK;

  constructor() { }

  ngOnInit(): void {
  }

}

export enum Label {
  STOCK,
  ORDERS,
  WORKERS
}
