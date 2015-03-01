<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html>
<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="simulator">
  <html>
  <body>
    <h2><xsl:text>Project: </xsl:text><xsl:value-of select="@name"/></h2>
    <xsl:for-each select="dueproxy">
		<br/><h3><xsl:text>DUEPROXY '</xsl:text><xsl:value-of select="@name"/><xsl:text>' ip:</xsl:text><xsl:value-of select="@ip"/></h3>
		<xsl:apply-templates/>
    </xsl:for-each>	
  </body>
  </html>
</xsl:template>

<xsl:template match="I2C_IO">
	<p>
		<table border="1">
		  <th bgcolor="#66FF66" colspan="5" style="text-align:left">
			<b><xsl:text>I2C_IO [</xsl:text><xsl:value-of select="@subaddr"/><xsl:text>] </xsl:text><xsl:value-of select="@name"/></b>
		  </th>
		  <tr bgcolor="#C8FFC8">
			<th width="80" style="text-align:left">Type</th>
			<th width="150" style="text-align:left">Name</th>
			<th width="40" style="text-align:left">#</th>
			<th width="400" style="text-align:left">Description</th>
			<th width="600" style="text-align:left">dataref</th>
		  </tr>
			<xsl:apply-templates/>
		</table>
	</p>
</xsl:template>

<xsl:template match="SPI_LDISP">
	<p>
		 
		<table border="1">
		  <th bgcolor="#FF6464" colspan="6" style="text-align:left">
			<b><xsl:text>SPI_LDISP [</xsl:text><xsl:value-of select="@subaddr"/><xsl:text>] #dev:</xsl:text><xsl:value-of select="@nrdevices"/><xsl:text> </xsl:text><xsl:value-of select="@name"/></b>
		  </th>
			  <tr bgcolor="#F7C8C8">
				<th width="80" style="text-align:left">Type</th>
				<th width="150" style="text-align:left">Name</th>
				<th width="40" style="text-align:left">#</th>
				<th width="40" style="text-align:left">nr</th>
				<th width="354" style="text-align:left">Description</th>
				<th width="600" style="text-align:left">dataref</th>
			  </tr>
			  <xsl:apply-templates/>
		</table>
	</p>
</xsl:template>

<xsl:template match="DUE_RESOURCE">
	<p>
		<table border="1">
		  <th bgcolor="#6464FF" colspan="7" style="text-align:left">
			<b><xsl:text>DUE_RESOURCE</xsl:text></b>
		  </th>
		  <tr bgcolor="#C8C8FF">
			<th width="80" style="text-align:left">Type</th>
			<th width="150" style="text-align:left">Name</th>
			<th width="34" style="text-align:left">#</th>
			<th width="34" style="text-align:left">div</th>
			<th width="34" style="text-align:left">off</th>
			<th width="326" style="text-align:left">description</th>
			<th width="600" style="text-align:left">dataref</th>
		  </tr>
			<xsl:apply-templates/>
		</table>
	</p>
</xsl:template>

<xsl:template match="IO">
	<tr bgcolor="#E6FFE6">
		<th style="text-align:left">IO</th>
		<th style="text-align:left"><xsl:value-of select="@name"/></th>
		<th style="text-align:left"><xsl:value-of select="@bit"/></th>
		<th style="text-align:left"><xsl:value-of select="@description"/></th>
		<th style="text-align:left"><xsl:value-of select="@dataref"/></th>
     </tr>
</xsl:template>

<xsl:template match="DISPLAY">
	<tr bgcolor="#FFE6E6">
		<th style="text-align:left">DISPLAY</th>
		<th style="text-align:left"><xsl:value-of select="@name"/></th>
		<th style="text-align:left"><xsl:value-of select="@first_digit"/></th>
		<th style="text-align:left"><xsl:value-of select="@nr_digits"/></th>
		<th style="text-align:left"><xsl:value-of select="@description"/></th>
		<th style="text-align:left"><xsl:value-of select="@dataref"/></th>
     </tr>
</xsl:template>

<xsl:template match="LED">
	<tr bgcolor="#E6E6E6">
		<th style="text-align:left">LED</th>
		<th style="text-align:left"><xsl:value-of select="@name"/></th>
		<th style="text-align:left"><xsl:value-of select="@bit"/></th>
		<th style="text-align:left"></th>
		<th style="text-align:left"><xsl:value-of select="@description"/></th>
		<th style="text-align:left"><xsl:value-of select="@dataref"/></th>
     </tr>
</xsl:template>

<xsl:template match="DUE_IO">
	<tr bgcolor="#E6E6FF">
		<th style="text-align:left">DUE_IO</th>
		<th style="text-align:left"><xsl:value-of select="@name"/></th>
		<th style="text-align:left"><xsl:value-of select="@pin"/></th>
		<th />
		<th />
		<th style="text-align:left"><xsl:value-of select="@description"/></th>
		<th style="text-align:left"><xsl:value-of select="@dataref"/></th>
     </tr>
</xsl:template>

<xsl:template match="ADC">
	<tr bgcolor="#E6E6FF">
		<th style="text-align:left">ADC</th>
		<th style="text-align:left"><xsl:value-of select="@name"/></th>
		<th style="text-align:left"><xsl:value-of select="@pin"/></th>
		<th style="text-align:left"><xsl:value-of select="@divide"/></th>
		<th style="text-align:left"><xsl:value-of select="@offset"/></th>
		<th style="text-align:left"><xsl:value-of select="@description"/></th>
		<th style="text-align:left"><xsl:value-of select="@dataref"/></th>
     </tr>
</xsl:template>

<xsl:template match="PWM">
	<tr bgcolor="#E6E6FF">
		<th style="text-align:left">PWM</th>
		<th style="text-align:left"><xsl:value-of select="@name"/></th>
		<th style="text-align:left"><xsl:value-of select="@pin"/></th>
		<th style="text-align:left"></th>
		<th style="text-align:left"></th>
		<th style="text-align:left"><xsl:value-of select="@description"/></th>
		<th style="text-align:left"><xsl:value-of select="@dataref"/></th>
     </tr>
</xsl:template>

<xsl:template match="IHEX">
</xsl:template>

</xsl:stylesheet>
