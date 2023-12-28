/**********************************************
 * Self-Driving Car Nano-degree - Udacity
 *  Created on: December 11, 2020
 *      Author: Mathilde Badoual
 **********************************************/

#include "pid_controller.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kpi, double Kii, double Kdi, double output_lim_maxi, double output_lim_mini) {
   /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   **/
  this->Kp = Kpi;
  this->Ki = Kii;
  this->Kd = Kdi;
  this->output_lim_max = output_lim_maxi;
  this->output_lim_min = output_lim_mini;
  this->i_err = 0.0;
  this->d_err = 0.0;
  this->p_err = 0.0;
  this->dt = 0.0;
}


void PID::UpdateError(double cte) {
   /**
   * TODO: Update PID errors based on cte.
   **/
   this->i_err += cte*this->dt;
   if (this->dt > 0.0) {
      this->d_err = (cte - this->p_err) / this->dt;
   }
   else {
      this->d_err = 0.0;
   }

   this->p_err = cte;
}

double PID::TotalError() {
   /**
   * TODO: Calculate and return the total error
    * The code should return a value in the interval [output_lim_mini, output_lim_maxi]
   */
   double control;

   control = this->Kp * this->p_err + this->Kd * this->d_err + this->Ki * this->i_err;

   // If control exceeds limits, clamp it
   if (control > this->output_lim_max) {
      control = this->output_lim_max;
   }
   else if (control < this->output_lim_min){
      control = this->output_lim_min;
   }

    return control;
}

double PID::UpdateDeltaTime(double new_delta_time) {
   /**
   * TODO: Update the delta time with new value
   */
  this->dt = new_delta_time;
  return this->dt;
}