/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2019 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::pulseFixedValueFvPatchField

Description
    This boundary condition provides a pulseFixedValue condition,
    calculated as:

        \f[
            Q = Q_{0} + Q_{p} + s*Q_{t}
        \f]

    where
    \vartable
        s      | single scalar value [units]
        Q_{0}  | single Type value [units]
        Q_{p}  | Type field across patch [units]
        Q_{t}  | Type function of time [units]
    \endtable

Usage
    \table
        Property   | Description                  | Req'd? | Default
        scalarData | single scalar value          | yes    |
        data       | single Type value          | yes    |
        fieldData  | Type field across patch    | yes    |
        timeVsData | Type function of time      | yes    |
        wordData   | word, eg name of data object | no     | wordDefault
    \endtable

    Example of the boundary condition specification:
    \verbatim
    <patchName>
    {
        type       pulseFixedValue;
        scalarData -1;
        data       1-or-(1 0 0);
        fieldData  uniform 3-or-(3 0 0);
        timeVsData table (
                             (0 0-or-(0 0 0))
                             (1 2-or-(2 0 0))
                          );
        wordName   anotherName;
        value      uniform 4-or-(4 0 0); // optional initial value
    }
    \endverbatim

SourceFiles
    pulseFixedValueFvPatchField.C

\*---------------------------------------------------------------------------*/

#ifndef pulseFixedValueFvPatchField_H
#define pulseFixedValueFvPatchField_H

#include "fixedValueFvPatchFields.H"
#include "Function1.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
     Class pulseFixedValueFvPatchField Declaration
\*---------------------------------------------------------------------------*/

template<class Type>
class pulseFixedValueFvPatchField
:
    public fixedValueFvPatchField<Type>
{
    // Private data

        //- Cycle period [s]
        scalar period_;

        //- Duration of pulse as a fraction of period
        scalar duration_;

        //- Base value of the field, defaults to zero
        Type baseValue_;

        //- Value during the pulse
        Field<Type> pulseValue_;
        

    // Private Member Functions

        //- Return current time
        scalar pulseFraction() const;


public:

    //- Runtime type information
    TypeName("pulseFixedValue");


    // Constructors

        //- Construct from patch and internal field
        pulseFixedValueFvPatchField
        (
            const fvPatch&,
            const DimensionedField<Type, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        pulseFixedValueFvPatchField
        (
            const fvPatch&,
            const DimensionedField<Type, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given fixedValueTypeFvPatchField
        //  onto a new patch
        pulseFixedValueFvPatchField
        (
            const pulseFixedValueFvPatchField<Type>&,
            const fvPatch&,
            const DimensionedField<Type, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct as copy
        pulseFixedValueFvPatchField
        (
            const pulseFixedValueFvPatchField<Type>&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchField<Type>> clone() const
        {
            return tmp<fvPatchField<Type>>
            (
                new pulseFixedValueFvPatchField<Type>(*this)
            );
        }

        //- Construct as copy setting internal field reference
        pulseFixedValueFvPatchField
        (
            const pulseFixedValueFvPatchField<Type>&,
            const DimensionedField<Type, volMesh>&
        );

        //- Construct and return a clone setting internal field reference
        virtual tmp<fvPatchField<Type>> clone
        (
            const DimensionedField<Type, volMesh>& iF
        ) const
        {
            return tmp<fvPatchField<Type>>
            (
                new pulseFixedValueFvPatchField<Type>
                (
                    *this,
                    iF
                )
            );
        }


    // Member functions

        // Mapping functions

            //- Map (and resize as needed) from self given a mapping object
            virtual void autoMap
            (
                const fvPatchFieldMapper&
            );

            //- Reverse map the given fvPatchField onto this fvPatchField
            virtual void rmap
            (
                const fvPatchField<Type>&,
                const labelList&
            );


        // Evaluation functions

            //- Update the coefficients associated with the patch field
            virtual void updateCoeffs();


        //- Write
        virtual void write(Ostream&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "pulseFixedValueFvPatchField.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
