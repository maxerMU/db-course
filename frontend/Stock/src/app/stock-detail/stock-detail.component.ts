import { Component, OnInit, Input } from '@angular/core';
import { StockDetail } from '../stock-detail';

@Component({
  selector: 'app-stock-detail',
  templateUrl: './stock-detail.component.html',
  styleUrls: ['./stock-detail.component.less']
})
export class StockDetailComponent implements OnInit {
  @Input() detail?: StockDetail;

  constructor() { }

  ngOnInit(): void {
  }

}
