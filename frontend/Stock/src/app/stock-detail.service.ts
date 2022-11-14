import { Injectable } from '@angular/core';
import { StockDetail, DetailInStock } from './stock-detail';
import { HttpClient, HttpParams } from '@angular/common/http';
import { map, switchMap, timeout } from 'rxjs/operators'
import { combineLatest, forkJoin, Observable, of } from 'rxjs';
import { Order } from './order';
import { AuthService } from './auth.service';
import { Worker } from './worker';
import { environment } from 'src/environments/environment';

@Injectable({
  providedIn: 'root'
})
export class StockDetailService {

  constructor(private http: HttpClient,
              private authService: AuthService) { }

  getDetailsInStock(): Observable<StockDetail[]> {
    return this.http.get<DetailsInStock>(this.stockDetailsUrl).pipe(
      timeout(3000),
      map((res: DetailsInStock) => res.details),
      map((details: DetailInStock[]) => {
        return details.map((stockDetail: DetailInStock) => {
          return this.http.get<Detail>(this.detailsUrl + '/' + stockDetail.part_number).pipe(
            timeout(3000),
            map((detail: Detail) => {
              const detailWithQuantity: DetailWithQuantity = {
                part_number: detail.part_number,
                name_rus: detail.name_rus,
                name_eng: detail.name_eng,
                producer_id: detail.producer_id,
                quantity: stockDetail.quantity
              }

              return detailWithQuantity;

            })
          )
        })
      }),
      switchMap((array: Observable<DetailWithQuantity>[]) => forkJoin(array)),
      switchMap((detailsWithQuantity: DetailWithQuantity[]) => {
        return combineLatest(detailsWithQuantity.map((detail: DetailWithQuantity) => {
          return this.getProducer(detail.producer_id).pipe(
            map((producer: Producer) => {
              const stockDetail: StockDetail = {
                part_number: detail.part_number,
                part_name: detail.name_eng,
                producer_name: producer.name,
                producer_country: producer.country,
                amount: detail.quantity
              }

              return stockDetail;
            })

          )
        }))
      })
    )
  }

  getDetail(part_number: string): Observable<Detail> {
    return this.http.get<Detail>(this.detailsUrl + '/' + part_number);
  }

  getProducer(id: number): Observable<Producer> {
    return this.http.get<Producer>(this.producersUrl + '/' + id.toString());
  }

  getOrders(time_start: string, time_end: string): Observable<Order[]> {
    let params = new HttpParams();
    params = params.set('time_start', time_start);
    params = params.set('time_end', time_end);

    return this.http.get<StockLogs>(this.logsUrl, {params: params}).pipe(
      map((logs: StockLogs) => logs.logs),
      map((logs: StockLog[]) => {
        return logs.map((log: StockLog) => {
          return this.authService.getWorker(log.worker_id).pipe(
            map((worker: Worker) => {
              const order: Order = {
                detail: log.detail_id,
                worker: worker.name + ' ' + worker.surname,
                change: log.change,
                date: log.time_change
              }
              return order;
            })
          )
        })
      }),
      switchMap((array: Observable<Order>[]) => forkJoin(array)),
    );
  }

  takeDetailFromStock(order: DetailInStock) {
    return this.http.delete(this.stockDetailsUrl, {body: order});
  }

  putDetailInStock(order: DetailInStock) {
    return this.http.post(this.stockDetailsUrl, order);
  }

  private stockDetailsUrl = environment.baseApiUrl + '/api/v1/stock'
  private logsUrl = environment.baseApiUrl + '/api/v1/stock/logs'
  private detailsUrl = environment.baseApiUrl + '/api/v1/details'
  private producersUrl = environment.baseApiUrl + '/api/v1/producers'
}

interface Detail {
  part_number: string;
  name_rus: string;
  name_eng: string;
  producer_id: number;
}

export interface DetailWithQuantity extends Detail {
  quantity: number
}

interface Producer {
  id: number;
  name: string;
  country: string;
}

interface DetailsInStock {
  details: DetailInStock[];
}

interface StockLog {
  change: number;
  detail_id: string;
  time_change: string;
  worker_id: number;
}

interface StockLogs {
  logs: StockLog[];
}