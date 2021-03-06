/*=========================================================================

Program:   VMTK
Module:    $RCSfile: vtkbvsGradientMagnitudeRecursiveGaussianImageFilter.cxx,v $
Language:  C++
Date:      $Date: 2006/04/06 16:48:25 $
Version:   $Revision: 1.1 $

  Copyright (c) Luca Antiga, David Steinman. All rights reserved.
  See LICENSE file for details.

  Portions of this code are covered under the VTK copyright.
  See VTKCopyright.txt or http://www.kitware.com/VTKCopyright.htm 
  for details.

  Portions of this code are covered under the ITK copyright.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm
  for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "vtkvmtkGradientMagnitudeRecursiveGaussianImageFilter.h"
#include "vtkObjectFactory.h"

#include "vtkvmtkITKFilterUtilities.h"

#include "itkGradientMagnitudeRecursiveGaussianImageFilter.h"

vtkStandardNewMacro(vtkvmtkGradientMagnitudeRecursiveGaussianImageFilter);

vtkvmtkGradientMagnitudeRecursiveGaussianImageFilter::vtkvmtkGradientMagnitudeRecursiveGaussianImageFilter()
{
  this->Sigma = 1.0;
  this->NormalizeAcrossScale = 0;
}

void vtkvmtkGradientMagnitudeRecursiveGaussianImageFilter::SimpleExecute(vtkImageData* input, vtkImageData* output)
{
  typedef itk::Image<float,3> ImageType;

  ImageType::Pointer inImage = ImageType::New();

  vtkvmtkITKFilterUtilities::VTKToITKImage<ImageType>(input,inImage);

  typedef itk::GradientMagnitudeRecursiveGaussianImageFilter<ImageType,ImageType> GradientMagnitudeFilterType;

  GradientMagnitudeFilterType::Pointer gradientMagnitudeFilter = GradientMagnitudeFilterType::New();
  gradientMagnitudeFilter->SetInput(inImage);
  gradientMagnitudeFilter->SetSigma(this->Sigma);
  gradientMagnitudeFilter->SetNormalizeAcrossScale(this->NormalizeAcrossScale);
  gradientMagnitudeFilter->Update();

  vtkvmtkITKFilterUtilities::ITKToVTKImage<ImageType>(gradientMagnitudeFilter->GetOutput(),output);
}

