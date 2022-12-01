import { Component, OnInit } from '@angular/core';
import { AuthService } from '../auth.service';
import { Label } from '../left-bar/left-bar.component';
import { Worker } from '../worker';

@Component({
  selector: 'app-workers',
  templateUrl: './workers.component.html',
  styleUrls: ['./workers.component.less']
})
export class WorkersComponent implements OnInit {
  workers: Worker[] = [];
  label: Label = Label.WORKERS

  constructor(private authService: AuthService) { }

  ngOnInit(): void {
    this.getWorkers()
  }

  getWorkers() {
    this.authService.getWorkers().subscribe(res => this.workers = res);
  }

  promote(id: number, curPrivilege: number) {
    this.authService.updatePrivilege(id, curPrivilege - 1).subscribe();
    let i = this.workers.findIndex((worker) => worker.id == id);
    this.workers[i].privilege = curPrivilege - 1;
  }

  downgrade(id: number, curPrivilege: number) {
    this.authService.updatePrivilege(id, curPrivilege + 1).subscribe();
    let i = this.workers.findIndex((worker) => worker.id == id);
    this.workers[i].privilege = curPrivilege + 1;
  }
}
