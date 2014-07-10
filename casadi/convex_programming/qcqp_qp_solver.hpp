/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010 by Joel Andersson, Moritz Diehl, K.U.Leuven. All rights reserved.
 *
 *    CasADi is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    CasADi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with CasADi; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef QCQP_QP_SOLVER_HPP
#define QCQP_QP_SOLVER_HPP

#include "casadi/core/function/qp_solver.hpp"
#include <casadi/convex_programming/casadi_qpsolver_qcqp_export.h>

namespace casadi {


// Forward declaration of internal class
class QCQPQPInternal;

  /** \brief Use a QCQP solver to solve q QP

   @copydoc QPSolver_doc

   \author Joris Gillis
   \date 2013
  */
class CASADI_QPSOLVER_QCQP_EXPORT QCQPQPSolver : public QPSolver {
public:

  /** \brief  Default constructor */
  QCQPQPSolver();


  /** \brief Constructor
  *  \param st Problem structure
  *  \copydoc scheme_QPStruct
  */
  explicit QCQPQPSolver(const QPStructure & st);

  /** \brief  Access functions of the node */
  QCQPQPInternal* operator->();
  const QCQPQPInternal* operator->() const;

  /// Check if the node is pointing to the right type of object
  virtual bool checkNode() const;

  /// Static creator function
  #ifdef SWIG
  %callback("%s_cb");
  #endif
  static QPSolver creator(const QPStructure & st) { return QCQPQPSolver(st);}
  #ifdef SWIG
  %nocallback;
  #endif

  /// Access underlying QCQP solver
  QCQPSolver & getSolver();

};


} // namespace casadi

#endif //QCQP_QP_SOLVER_HPP

