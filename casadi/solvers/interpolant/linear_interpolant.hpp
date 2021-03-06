/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010-2014 Joel Andersson, Joris Gillis, Moritz Diehl,
 *                            K.U. Leuven. All rights reserved.
 *    Copyright (C) 2011-2014 Greg Horn
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


#ifndef CASADI_LINEAR_INTERPOLANT_HPP
#define CASADI_LINEAR_INTERPOLANT_HPP

#include "casadi/core/interpolant_impl.hpp"
#include <casadi/solvers/interpolant/casadi_interpolant_linear_export.h>

/** \defgroup plugin_Interpolant_linear
*/

/** \pluginsection{Interpolant,linear} */

/// \cond INTERNAL

namespace casadi {
  /** \brief \pluginbrief{Interpolant,linear}
    Implements a multilinear interpolant: For 1D, the interpolating polynomial
    will be linear. For 2D, the interpolating polynomial will be bilinear, etc.

    @copydoc Interpolant_doc
    @copydoc plugin_Interpolant_linear
    \author Joel Andersson
    \date 2016
  */
  class CASADI_INTERPOLANT_LINEAR_EXPORT LinearInterpolant : public Interpolant {
  public:
    // Constructor
    LinearInterpolant(const std::string& name,
                      const std::vector<double>& grid,
                      const std::vector<int>& offset,
                      const std::vector<double>& values);

    // Destructor
    ~LinearInterpolant() override;

    // Get name of the plugin
    const char* plugin_name() const override { return "linear";}

    /** \brief  Create a new Interpolant */
    static Interpolant* creator(const std::string& name,
                                const std::vector<double>& grid,
                                const std::vector<int>& offset,
                                const std::vector<double>& values) {
      return new LinearInterpolant(name, grid, offset, values);
    }

    // Initialize
    void init(const Dict& opts) override;

    /// Evaluate numerically
    void eval(void* mem, const double** arg, double** res, int* iw, double* w) const override;

    ///@{
    /** \brief Full Jacobian */
    bool hasFullJacobian() const override { return true;}
    Function getFullJacobian(const std::string& name,
                                      const std::vector<std::string>& i_names,
                                      const std::vector<std::string>& o_names,
                                      const Dict& opts) override;
    ///@}

    /** \brief Is codegen supported? */
    bool has_codegen() const override { return true;}

    /** \brief Generate code for the body of the C function */
    void generateBody(CodeGenerator& g) const override;

    /// A documentation string
    static const std::string meta_doc;

    ///@{
    /** \brief Options */
    static Options options_;
    const Options& get_options() const override { return options_;}
    ///@}

    std::vector<int> lookup_mode_;
  };

  /** First order derivatives */
  class CASADI_INTERPOLANT_LINEAR_EXPORT LinearInterpolantJac : public FunctionInternal {
  public:
    /// Constructor
    LinearInterpolantJac(const std::string& name) : FunctionInternal(name) {}

    /// Destructor
    ~LinearInterpolantJac() override {}

    /** \brief Get type name */
    std::string type_name() const override { return "interpolant_linear_jac";}

    /** \brief Is codegen supported? */
    bool has_codegen() const override { return true;}

    /** \brief Generate code for the body of the C function */
    void generateBody(CodeGenerator& g) const override;

    // Initialize
    void init(const Dict& opts) override;

    /// Evaluate numerically
    void eval(void* mem, const double** arg, double** res, int* iw, double* w) const override;
  };

} // namespace casadi

/// \endcond
#endif // CASADI_LINEAR_INTERPOLANT_HPP
